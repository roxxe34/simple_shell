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
/**
 *print - prints a string to stdout
 *@string: string to be printed
 *@stream: stream to print out to
 *
 *Return: void, return nothing
 */
void print(char *string, int stream)
{
	int i = 0;

	for (; string[i] != '\0'; i++)
		write(stream, &string[i], 1);
}
/**
 * my_strchr - Locates the first occurrence of a character in a string.
 * @str: The input null-terminated string to search in.
 * @c: The character to be located in the string.
 *
 * Return: A pointer to the first occurrence of the character
 *          'c' in the string 'str', or NULL if the character is not found.
 */
char *my_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}

	return (NULL);
}
