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
* execute_single_command - function that execute single commands
* @tokens: token that contain command
*/
void execute_single_command(char *tokens[])
{
	if (_strcmp(tokens[0], "exit") == 0)
	{
		handle_exit_command(tokens, 1);
	}
	else
	{
		execute_command(tokens);
	}
}
/**
 * execute_input - execute a shell command
 * @input: input string
*/
void execute_input(char *input)
{
	char *commands[MAX_TOKENS];
	int command_count = 0;
	char *token;
	int i;

	token = my_strtok(input, ";");
	while (token != NULL && command_count < MAX_TOKENS)
	{
		commands[command_count] = token;
		command_count++;
		token = my_strtok(NULL, ";");
	}

	for (i = 0; i < command_count; i++)
	{
		char *command = commands[i];
		char *tokens[MAX_TOKENS];
		int count = tokenize(command, tokens);

		if (count == 0)
		{
			print(shell_name, STDERR_FILENO);
			fprintf(stderr, "Invalid input: %s\n", command);
		}
		else
		{
			execute_single_command(tokens);
			freetok(tokens, count);
		}
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
