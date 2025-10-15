#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Berfore execlp()\n");
    execlp("ls", "ls", "-l", NULL); //Searches in PATH Env variable, P in execlp represents -> Path
    printf("Error: execlp()\n");
    return 0;
}