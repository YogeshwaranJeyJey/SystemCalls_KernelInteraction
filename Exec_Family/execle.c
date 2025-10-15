#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Berfore execle()\n");
    char *env_args[] = {
        "MYVAR=HelloWorld",
        "PATH=/usr/bin:/bin",
        NULL};
    execle("/usr/bin/env", "env", NULL, env_args);
    printf("Error: execle()\n");
    return 0;
}