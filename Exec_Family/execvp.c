#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before execvp()\n");
    char *args[] = {"ls", "-l",  NULL}; //Args as array or vector
    execvp("ls", args); //Searches in PATH Env variable, P in execlp represents -> Path
    printf("Error: execvp()\n");
    return 0;
}
