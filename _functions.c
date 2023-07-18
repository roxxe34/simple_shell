
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

void execute_command(char *tokens[]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        if (execve(tokens[0], tokens, NULL) == -1)
        {
            fprintf(stderr, "%s: Command not found\n", tokens[0]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int status;
        wait(&status);
    }
}

int tokenize(char *buffer, char *tokens[]) {
    char *delim = " \n";
    int count = 0;

    char *token = strtok(buffer, delim);
    while (token != NULL && count < MAX_TOKENS) {
        tokens[count] = token;
        count++;
        token = strtok(NULL, delim);
    }

    tokens[count] = NULL;
    return count;
}

int _strcmp(char *s1, char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
void freetok(char *tokens[]){
     for (int i = 0; i < count; i++) 
         {
        free(tokens[i]);
         }
        return (0);
}
