#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int sharedVariable = 100;

void* worker(void* arg){
    printf("Worker thread started!\n");
    sharedVariable += 20;
    printf("The shared variable at worker thread is %d\n", sharedVariable);
    printf("Worker thread finished!\n");
}

int main(){
    printf("The shared variable at the start: %d\n", sharedVariable);
    int pid = fork();

    if(pid < 0){
        perror("Fork failed!\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        printf("[Child process]: %d\n", getpid());
        sharedVariable += 50;
        printf("The shared variable modified by child: %d\n", sharedVariable);
        printf("Child Process completed!\n");
        exit(EXIT_SUCCESS);
    }
    else{
        wait(NULL);
        printf("[Parent process]: %d\n", getpid());
        printf("The shared variable inside Parent: %d\n", sharedVariable);
        printf("Parent Process completed!\n");

        pthread_t t1;
        printf("Main thread started from parent!\n");
        printf("The shared variable at main thread: %d\n", sharedVariable);
        
        if(pthread_create(&t1, NULL, worker, NULL) != 0){
            perror("Thread creation failed!\n");
            exit(EXIT_FAILURE);
        }

        pthread_join(t1, NULL);

        printf("The shared variable at main thread: %d\n", sharedVariable);
        printf("Main thread finished!\n");
    }
    return 0;
}