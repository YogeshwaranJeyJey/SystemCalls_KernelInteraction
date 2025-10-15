#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before execvpe()\n");

    char *args[] = {"env", NULL};  // Command-line arguments
    char *my_env[] = {
        "MYVAR=HelloFromExecvpe",
        "PATH=/usr/bin:/bin",
        NULL
    };

    execvpe("env", args, my_env);

    perror("execvpe failed");  // Only runs if exec fails
    return 0;
}
