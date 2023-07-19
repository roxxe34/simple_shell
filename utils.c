#include "shell.h"

int is_number(const char* str)
{
	int i;
	for (i = 0; str[i] != '\0'; i++) {
		if (!isdigit(str[i])) {
			return (0);
		}
	}
	return (1);
}


char *_str_search(char *s, char c)
{
	int i = 0;

	for (; s[i] != c && s[i] != '\0'; i++)
		;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}

/**
 * _atoi - Convert a string to an integer.
 * @s: The pointer to convert
 *
 * Return: A integer
 */
int _atoi(char *s)
{
	int c = 0;
	unsigned int ni = 0;
	int min = 1;
	int isi = 0;

	while (s[c])
	{
		if (s[c] == 45)
		{
			min *= -1;
		}

		while (s[c] >= 48 && s[c] <= 57)
		{
			isi = 1;
			ni = (ni * 10) + (s[c] - '0');
			c++;
		}

		if (isi == 1)
		{
			break;
		}

		c++;
	}

	ni *= min;
	return (ni);
}
/**
 * _strdup - duplicate to new memory space location
 * @str: char
 * Return: 0
 */
char* _strdup(const char* str)
{
	size_t len;
	char* new_str;
	if (str == NULL) {
		return (NULL);
	}
	len = _strlen(str);
	new_str = (char*)malloc((len + 1) * sizeof(char));

	if (new_str != NULL) {

		_strcpy(new_str, str);
	}

	return (new_str);
}
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2) {
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
