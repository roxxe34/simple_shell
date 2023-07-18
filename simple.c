#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    while (1)
    {
        char *tokens[MAX_TOKENS];
        char *buffer = NULL;
        size_t len = 0;
        ssize_t read;
	int count = 0;
        printf("$ ");
        read = getline(&buffer, &len, stdin);
        if (read == EOF || _strcmp(buffer, "exit\n") == 0)
        {
            free(buffer);
            return 0;
        }

        count = tokenize(buffer, tokens);

        if (count == 0)
        {
            fprintf(stderr, "Invalid input\n");
            free(buffer);
            continue;
        }else if (count >= 1){
		execute_command(tokens);
		free(buffer);
	}
    }
}
