#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before execve()\n");

    char *args[] = {"ls", "-l", "/usr", NULL};        // Command-line arguments
    char *env[]  = {"PATH=/usr/bin:/bin", NULL};     // Environment variables

    execve("/usr/bin/ls", args, env);               // Run ls

    perror("execve failed");                         // Only runs if execve fails
    return 0;
}
