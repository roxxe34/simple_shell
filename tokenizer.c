#include "shell.h"

char *_getenviron(char *name)
{
	extern char **environ;

	char *pair_ptr;
	char *name_cpy;

	for (; *environ != NULL; environ++)
	{
		for (pair_ptr = *environ, name_cpy = name;
			 *pair_ptr == *name_cpy; pair_ptr++, name_cpy++) {
			if (*pair_ptr == '=')
				break;
		}
		if ((*pair_ptr == '=') && (*name_cpy == '\0'))
			return (pair_ptr + 1);
	}
	return (NULL);
}

char *my_strtok(char *str, const char *delim)
{
	static char *token;
	static char *nextToken;
	char *result;

	if (str != NULL)
	{
		token = str;
	}

	if (token == NULL || *token == '\0')
	{
		return (NULL);
	}

	result = token;
	nextToken = _strpbrk(token, delim);

	if (nextToken != NULL)
	{
		*nextToken = '\0';
		token = nextToken + 1;
	} else
	{
		token += _strlen(token);
	}

	return (result);
}

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

void freetok(char *tokens[], int count)
{
	int i;
	for (i = 0; i < count; i++)
	{
		free(tokens[i]);
	}
}
/**
 * strpbrk - Searches for the first occurrence of any character from `str2` in `str1`.
 * @str1: The input null-terminated string to be searched.
 * @str2: The input null-terminated string containing the set of characters to search for.
 *
 * Return: If any character from `str2` is found in `str1`, a pointer to the first occurrence
 *		 of that character in `str1`. Otherwise, returns NULL.
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