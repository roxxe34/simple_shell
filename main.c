#include "shell.h"
/**
 * main - Main function that starts the simple shell.
 * @argv: command line arguments
 * @argc: command line arguments
 * Return: Always 0.
 */

int main(int argc, char **argv)
{
	char *line;
	char *tokens[MAX_TOKENS];
	size_t len;
	ssize_t read;
	int count;
	char *shell_name = argv[0];

	if (argc == 2)
	{
		FILE *file = fopen(argv[1], "r");

		if (!file)
		{
			print(shell_name, STDERR_FILENO);
			perror("Error opening file");
			return (1);
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
		free(line);
		fclose(file);
	}
	else
	{
		read_input_and_execute(argc, argv);
	}
	return (0);
}
