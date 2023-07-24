#include "shell.h"
char *shell_name = NULL;
/**
 * read_input - read input from user
 * @is_interactive: variable indicating if the shell is interactive.
 * Return: line number of input
*/
char *read_input(int *is_interactive)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	if (*is_interactive)
	{
		printf("$ ");
		fflush(stdout);
	}

	read = my_getline(&line, &len, stdin);
	if (read == -1 || _strcmp(line, "exit\n") == 0)
	{
		free(line);
		return (NULL);
	}

	return (line);
}
/**
 * execute_input - execute a shell command
 * @input: input string
*/
void execute_input(char *input)
{
	char *tokens[MAX_TOKENS];
	int count = 0;

	count = tokenize(input, tokens);
	if (count == 0)
	{
		print(shell_name, STDERR_FILENO);
		fprintf(stderr, "Invalid input\n");
		return;
	}
	else if (count >= 1)
	{
		if (_strcmp(tokens[0], "exit") == 0)
		{
			handle_exit_command(tokens, count);
		}
		else
		{
			execute_command(tokens);
		}
		freetok(tokens, count);
	}
}
/**
 * handle_exit_command - Handle the "exit" command and exit the shell.
 * @tokens: An array of tokens representing the command and arguments.
 * @count: The number of tokens in the array.
 */
void handle_exit_command(char **tokens, int count)
{
	if (count == 2 && is_number(tokens[1]))
	{
		int status = _atoi(tokens[1]);

		freetok(tokens, count);
		my_exit(status);
	} else if (count == 1)
	{
		freetok(tokens, count);
		my_exit(0);
	} else
	{
		fprintf(stderr, "Invalid usage of 'exit'. Usage: exit status\n");
	}
}
/**
 * read_input_and_execute - Read user input and execute commands.
 * @argc: The number of arguments
 * @argv: The command of the command
 */
void read_input_and_execute(int argc __attribute__((unused)), char **argv)
{
	int is_interactive = isatty(STDIN_FILENO);

	shell_name = argv[0];

	while (1)
	{
		char *input = read_input(&is_interactive);

		if (input == NULL)
		{
			my_exit(0);
		}

		execute_input(input);
		free(input);
	}
}
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
