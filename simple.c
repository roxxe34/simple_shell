#include "shell.h"
char *shell_name = NULL;
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
 */
void read_input_and_execute(int argc __attribute__((unused)), char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	shell_name = argv[0];

	while (1)
	{
		char *tokens[MAX_TOKENS];
		int count = 0;
		char *command;

		printf("$ ");
		fflush(stdout);
		read = my_getline(&line, &len, stdin);
		if (read == -1 || _strcmp(line, "exit\n") == 0)
		{
			free(line);
			freetok(tokens, count);
			my_exit(0);
		}

		/*kfjdhkdsjhfkjsdhf*/
		command = my_strtok(line, ";");
		while (command != NULL) {
			count = tokenize(command, tokens);
			if (count == 0)
			{	
				print(shell_name, STDERR_FILENO);
				fprintf(stderr, "Invalid input\n");
				continue;
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
			command = my_strtok(NULL, ";");
		}
		/*kfjdhkdsjhfkjsdhf*/
	}
}
/**
 * main - Main function that starts the simple shell.
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	read_input_and_execute(argc, argv);
	return (0);
}
