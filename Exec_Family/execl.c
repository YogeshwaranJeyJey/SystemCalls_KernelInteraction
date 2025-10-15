#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Berfore execl()\n");
    execl("/usr/bin/ls", "ls", "-l", NULL); //Args as list
    printf("Error: execl()\n");
    return 0;
}