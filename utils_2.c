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
