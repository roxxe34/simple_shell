#include "shell.h"
/**
 * _getenviron - Searches for the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Return: If the environment variable is found, return a pointer to its value.
 *		 Otherwise, return NULL.
 */
char *_getenviron(const char *name)
{
	char **env;

	size_t name_len = _strlen(name);

	for (env = environ; *env != NULL; env++)
	{
		if (my_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{

			return (*env + name_len + 1);
		}
	}
	return (NULL);
}
/**
 * my_strtok - Tokenizes a string based on a given set of delimiters.
 * @str: The input string to be tokenized.
 * @delim: The set of delimiters used to tokenize the string.
 *
 * Return: A pointer to the next token found in the input string
 */
char *my_strtok(char *str, const char *delim)
{
	static char *token;
	static char *nextToken;
	char *result;

	if (str != NULL)
	{
		token = str;
	}

	if (token == NULL || *token == '\0' || *token == '#')
	{
		return (NULL);
	}

	while (*token != '\0' && my_strchr(delim, *token) != NULL)
	{
		token++;
	}

	result = token;
	nextToken = _strpbrk(token, delim);

	if (nextToken != NULL)
	{
		*nextToken = '\0';
		token = nextToken + 1;
	}
	else
	{
		token += _strlen(token);
	}

	return (result);
}
/**
 * tokenize - Tokenizes a string into an array of tokens.
 * @buffer: The input string to be tokenized.
 * @tokens: An array of strings to store the tokens.
 *
 * Return: The number of tokens found in the input string.
 */
int tokenize(char *buffer, char *tokens[])
{
	char *delim = " \n";
	int count = 0;
	char *token = my_strtok(buffer, delim);

	while (token != NULL && count < MAX_TOKENS)
	{
		tokens[count] = _strdup(token);
		count++;
		token = my_strtok(NULL, delim);
	}

	tokens[count] = NULL;
	return (count);
}
/**
 * freetok - Frees the memory used by the tokens array.
 * @tokens: An array of strings (tokens).
 * @count: The number of tokens in the array.
 */
void freetok(char *tokens[], int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		free(tokens[i]);
	}
}
/**
 * _strpbrk - Searches for the first occurrence of character from str2 in str1
 * @str1: The input null-ter string to be searched.
 * @str2: The input null-ter string containing the set of characters to be ser
 *
 * Return: If any character from str2 is found in str1, a pointer to the first
 *		 occurrence of that character in `str1`. Otherwise, returns NULL.
 */
char *_strpbrk(const char *str1, const char *str2)
{
	if (str1 == NULL || str2 == NULL)
		return (NULL);

	while (*str1)
	{
		const char *ptr = str2;

		while (*ptr)
		{
			if (*str1 == *ptr)
				return ((char *)str1);
			ptr++;
		}
		str1++;
	}

	return (NULL);
}
