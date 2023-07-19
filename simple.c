#include "shell.h"
/**
 * _strlen - Calculate the length of a null-terminated string.
 * @str: Pointer to the string.
 *
 * Return: The number of characters in the string.
 */
int _strlen(const char *str)
{
	int len = 0;

	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}
/**
 * _strcpy - Copy the contents of the source string to the destination string.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */

char *_strcpy(char *dest, const char *src)
{
	int a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';
	return (dest);
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
 */
void read_input_and_execute(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		char *tokens[MAX_TOKENS];
		int count = 0;

		printf("$ ");
		fflush(stdout);
		read = my_getline(&line, &len, stdin);
		if (read == -1 || _strcmp(line, "exit\n") == 0)
		{
			free(line);
			freetok(tokens, count);
			my_exit(0);
		}
		count = tokenize(line, tokens);
		if (count == 0)
		{
			fprintf(stderr, "Invalid input\n");
			continue;
		} else if (count >= 1)
		{
			if (_strcmp(tokens[0], "exit") == 0)
			{
				handle_exit_command(tokens, count);
			} else
			{
				execute_command(tokens);
			}
			freetok(tokens, count);
		}
	}
}
/**
 * main - Main function that starts the simple shell.
 * Return: Always 0.
 */
int main(void)
{
	read_input_and_execute();
	return (0);
}
