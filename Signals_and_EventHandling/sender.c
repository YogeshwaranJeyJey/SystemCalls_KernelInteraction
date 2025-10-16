#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    pid_t receiverPid = atoi(argv[1]);

    if(kill(receiverPid, SIGINT) != 0){
        perror("Kill");
        return 1;
    }
    printf("Signal sent successfully!\n");
    return 0;
}