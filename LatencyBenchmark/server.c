#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

#define BACKLOG 5
#define BUFFERSIZE  100  

void do_work() {
    int x = 0;
    for(int i = 0; i < 10000; i++){
        x += i;
    }
}

void handleConnection(int fd) {
    char buffer[BUFFERSIZE];
    ssize_t n;
    n = read(fd, buffer, sizeof(buffer) - 1);
    if(n < 0){
        perror("Read failed");
        close(fd);
        return;
    }
    buffer[n] = '\0';
    buffer[strcspn(buffer, "\r\n")] = 0;
    if (strcasecmp(buffer, "START") != 0) {
        const char *err_msg = "ERROR: Expected 'START'\n";
        write(fd, err_msg, strlen(err_msg));
        close(fd);
        return;
    }
    printf("Received valid command!, Started Working...\n");
    do_work();
    const char *resp = "DONE\n";
    ssize_t sent = write(fd, resp, strlen(resp));
    if (sent < 0) {
        perror("write failed");
        close(fd);
        return;
    }
    close(fd);
}
    
void * worker(void *arg) {
    int fd = (int)(intptr_t)arg;
    pthread_detach(pthread_self());
    handleConnection(fd);
    return NULL;
}

int main(int argc, char** argv){
    if(argc < 3){
        fprintf(stderr, "Usage: %s <port> <mode: fork|thread>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    char* mode = argv[2];

    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverFd < 0){
        perror("Socket creation failed!\n");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if(bind(serverFd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        perror("Binding failed!\n");
        exit(EXIT_FAILURE);
    }

    if(listen(serverFd, BACKLOG) < 0){
        perror("Listening failed!\n");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d mode=%s\n", port, mode);

    if(strcmp(mode, "fork") == 0){
        signal(SIGCHLD, SIG_IGN);
        while(1){
            struct sockaddr_in cli;
            socklen_t clilen = sizeof(cli);
            int fd = accept(serverFd, (struct sockaddr*)&cli, &clilen);
            if(fd < 0){
                if (errno == EINTR) continue;
                perror("accept"); break;
            }

            pid_t pid = fork();
            if(pid < 0){
                perror("Fork Failed!\n");
                close(fd);
            }
            else if(pid == 0){
                close(serverFd);
                handleConnection(fd);
                _exit(0);
            }
            else{
                close(fd);
            }

        }
    }
    else if(strcmp(mode, "thread") == 0){
        while(1){
            struct sockaddr_in cli;
            socklen_t clilen = sizeof(cli);
            int fd = accept(serverFd, (struct sockaddr*)&cli, &clilen);
            if(fd < 0){
                if (errno == EINTR) continue;
                perror("accept"); break;
            }

            pthread_t thread;
            if(pthread_create(&thread, NULL, worker, (void*)(intptr_t)fd) != 0){
                perror("Thread creation failed!\n");
                close(fd);
            }
        }
        
    }
    else{
        fprintf(stderr, "Unknown Mode: %s\n", mode);
        exit(EXIT_FAILURE);
    }
    close(serverFd);
    return 0;
}