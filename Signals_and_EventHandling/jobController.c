#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

pid_t childPid = -1;

void handler(int signum){
    if(childPid == -1){
        printf("No child process running!\n");
        return;
    }
    else if(signum == SIGUSR1){
        printf("Received SIGUSR1 -> Pausing the process!\n");
        kill(childPid, SIGSTOP);
    }
    else if(signum == SIGUSR2){
        printf("Received SIGUSR2 -> Resuming the process!\n");
        kill(childPid, SIGCONT);
    }
    else if(signum == SIGTERM){
        printf("Received SIGTERM -> Terminating the process!\n");
        kill(childPid, SIGTERM);
        waitpid(childPid, NULL, 0); 
        printf("[Parent] Exiting gracefully.\n");
        exit(0);
    }
    else if(signum == SIGINT){
        printf("Received SIGINT -> Cleaning the process!\n");
        if(childPid > 0){
            kill(childPid, SIGSTOP);
            waitpid(childPid, NULL, 0); 
            printf("[Parent] Exiting gracefully.\n");
            exit(0);
        }
        
    }
}

int main(){
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);

    childPid = fork();

    if(childPid < 0){
        perror("Fork");
        return 1;
    }
    else if(childPid == 0){
        printf("[Child Process with Pid: %d] is Running...\n", getpid());
        while(1){
            printf("Running...\n");
            sleep(3);
        }
    }
    else{
        while(1){
            printf("[Parent Process Pid: %d]\n", getpid());
            printf("Try kill -SIGUSR1 %d to Pause the child\n", getpid());
            printf("Try kill -SIGUSR2 %d to Resume the child\n", getpid());
            printf("Try kill -SIGTERM %d to Terminate the child\n", getpid());
            printf("Parent process waiting for signals...\n");
            pause();
        }
    }
    return 0;
}