#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signum){
    printf("Receiver received signal SIGINT\n");
}

int main(){
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    printf("[Receiver PID: %d]\n", getpid());
    printf("Waiting to receive signal...\n");

    while(1){
        pause();
    }
    return 0;
}