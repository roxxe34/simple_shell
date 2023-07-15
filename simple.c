#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_TOKENS 100

int main(int argc, char **argv)
{
    (void)argc;
    while (1)
    {
        char *buffer = NULL;
        size_t len = 0;
        ssize_t read;

        printf("$ ");
        read = getline(&buffer, &len, stdin);
        if (read == EOF)
        {
            free(buffer);
            return 0;
        }

        char *delim = " \n";
        char *tokens[MAX_TOKENS];
        int count = 0;

        char *token = strtok(buffer, delim);
        while (token != NULL)
        {
            tokens[count] = token;
            count++;
            token = strtok(NULL, delim);
        }

        if (count != 1)
        {
            fprintf(stderr, "Invalid input\n");
            free(buffer);
            continue;
        }

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            free(buffer);
            return 0;
        }
        else if (pid == 0)
        {
            if (execve(tokens[0], argv, NULL) == -1)
            {
                fprintf(stderr, "%s: Command not found\n", argv[0]);
                free(buffer);
                return 0;
            }
        }
        else
        {
            int status;
            wait(&status);
        }

        free(buffer);
    }

    return 0;
}
