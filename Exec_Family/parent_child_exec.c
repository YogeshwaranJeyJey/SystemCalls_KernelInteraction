#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(){
    int pid = fork();
    if(pid < 0){
        perror("Fork");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        printf("[Child process] with pid %d executing...\n", getpid());
        execl("/usr/bin/pwd", "pwd", NULL);
        perror("execl() failed\n");
    }
    else{
        printf("[Parent process] with pid %d waiting for child to finish...\n", getpid());
        wait(NULL);
        printf("[Child process] completed!\n");
        printf("[Parent process] completed\n");
    }
    return 0;
}

