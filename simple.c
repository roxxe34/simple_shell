#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"


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

        char *tokens[MAX_TOKENS];
        int count = tokenize(buffer, tokens);

        if (count != 1)
        {
            fprintf(stderr, "Invalid input\n");
            free(buffer);
            continue;
        }
        execute_command(tokens);
        free(buffer);
    }
}