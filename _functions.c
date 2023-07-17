#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

void execute_command(char *tokens[])
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        if (execve(tokens[0], tokens, tokens) == -1)
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
void tokenize(char *buffer, char *tokens[], int *count)
{
    char *delim = " \n";
    *count = 0;

    char *token = strtok(buffer, delim);
    while (token != NULL && *count < MAX_TOKENS)
    {
        tokens[(*count)++] = token;
        token = strtok(NULL, delim);
    }
}
