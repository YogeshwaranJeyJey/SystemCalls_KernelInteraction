#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before execv()\n");
    char *args[] = {"ls", "-l",  NULL}; //Args as array or vector
    execv("/usr/bin/ls", args);
    printf("Error: execv()\n");
    return 0;
}
