#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define COMMANDLENGTH   10
#define ARGSLENGTH  10

int main(){
    char command[COMMANDLENGTH];
    char* args[ARGSLENGTH];

    while(1){
        printf("yogeshwaran@jarvis: ");
        fflush(stdout);

        if(fgets(command, sizeof(command), stdin) == NULL){
            printf("\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0) 
            continue;
    
        if(strcmp(command, "exit") == 0)
            break;

        int i = 0;
        char *token = strtok(command, " ");
        while (token != NULL && i < ARGSLENGTH - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid_t pid = fork();

        if(pid < 0){
            perror("Fork");
            break;
        }
        else if(pid == 0){
            execvp(args[0], args);
            perror("execvp() failed");
            exit(EXIT_FAILURE);
        }
        else{
            wait(NULL);
        }
    }
    printf("yogeshwaran@jarvis: Exiting...\n");
    return 0;
}