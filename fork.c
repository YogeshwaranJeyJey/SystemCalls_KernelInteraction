#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Process Id: %d\n", getpid());

    int pid = fork();

    if(pid < 0){
        perror("Fork failed!\n");
        return 1;
    }
    else if(pid == 0){
        printf("[Child Process] PID: %d\n[Parent Process] PID: %d\n", getpid(), getppid());
    }
    else{
        printf("[Parent Process] PID: %d\n[Child Process] PID: %d\n", getpid(), pid);
    }

    printf("Process terminated! PID: %d\n", getpid());
    return 0;
}