#include "shell.h"
/**
 * main - Main function that starts the simple shell.
 * @argv: command line arguments
 * @argc: command line arguments
 * Return: Always 0.
 */
void* my_memcpy(void* dest, const void* src, size_t n)
{
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
	size_t i;

    for (i = 0; i < n; i++)
    {
        d[i] = s[i];
    }

    return dest;
}
void write_str_to_stderr(const char *str)
{
    write(STDERR_FILENO, str, _strlen(str));
}

int main(int argc, char **argv)
{
    char *line;
    char *tokens[MAX_TOKENS];
    size_t len;
    ssize_t read;
    int count;

    if (argc == 2)
    {
        int file = open(argv[1], O_RDONLY);
        if (file == -1)
        {
            perror("Error opening file");
            return 1;
        }

        line = NULL;
        len = 0;
        while ((read = my_getline(&line, &len, file)) != -1)
        {
            if (line[read - 1] == '\n')
                line[read - 1] = '\0';

            count = tokenize(line, tokens);

            if (count > 0)
            {
                execute_command(tokens);
                freetok(tokens, count);
            }
        }

        close(file);
        free(line);
    }
    else
    {
        line = NULL;
        len = 0;
        while (1)
        {
            printf("$ ");
            fflush(stdout);

            read = my_getline(&line, &len, STDIN_FILENO);
            if (read == -1)
            {
                if (line)
                    free(line);
                break;
            }

            if (line[read - 1] == '\n')
                line[read - 1] = '\0';

            count = tokenize(line, tokens);

            if (count > 0)
            {
                execute_command(tokens);
                freetok(tokens, count);
            }
        }

        free(line);
    }

    return 0;
}