#include "shell.h"

/**
 * e_puts - Print an input string.
 * @str: The string to be printed.
 * Return: Nothing.
 */
void e_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		eput_char(str[i]);
		i++;
	}
}

/**
 * eput_char - Write the character 'c' to stderr.
 * @c: The character to print.
 * Return: On success, 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int eput_char(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * put_fd - Write the character 'c' to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 * Return: On success, 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int put_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * put_sfd - Prints an input string.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 * Return: The number of characters put.
 */
int put_sfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += put_fd(*str++, fd);
	}
	return (i);
}
