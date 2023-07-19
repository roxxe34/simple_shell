#include "shell.h"
/**
 * my_strncmp - Compare the first 'n' characters of two strings.
 * @str1: Pointer to the first string.
 * @str2: Pointer to the second string.
 * @n: Number of characters to compare.
 *
 *	Return: 0 if the strings are equal up to 'n' characters.
 *	A negative value if the first string is lexicographically
 *	less than the second string.
 *	A positive value if the first string is lexicographically
 *	greater than the second string.
 */

int my_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		} else if (str1[i] == '\0')
		{
			return (0);
		}
	}
	return (0);
}
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


int main(void)
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
				if (count == 2 && is_number(tokens[1]))
				{
					int status = _atoi(tokens[1]);

					free(line);
					freetok(tokens, count);
					my_exit(status);
				} else if (count == 1)
				{
					free(line);
					freetok(tokens, count);
					my_exit(0);
				} else
				{
					fprintf(stderr, "Invalid usage of 'exit'. Usage: exit status\n");
				}
			} else
			{
				execute_command(tokens);
				freetok(tokens, count);
			}
		}
	}
	return (0);
}
