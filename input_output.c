#include "shell.h"
/**
 * initialize_buffer - Initializes the buffer for my_getline if necessary.
 * @lineptr: A pointer to a pointer to the line buffer.
 * @n: A pointer to the size of the buffer.
 *
 * If the line buffer is not allocated or its size is 0, this function
 * allocates memory for the buffer with the initial size defined by BUFFER_SIZE
 * If memory allocation fails, it displays an error message using perror.
 */
void initialize_buffer(char **lineptr, size_t *n)
{
	if (*lineptr == NULL || *n == 0)
	{
		*n = BUFFER_SIZE;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			perror("malloc");
			return;
		}
	}
}
/**
 * my_getline - Reads a line from the stream and stores it in lineptr.
 * @lineptr: Pointer to the line buffer.
 * @n: Pointer to the size of the buffer.
 * @stream: Stream to read the line from.
 *
 * Reads characters from the stream until the end of the line ('\n') or EOF.
 * Allocates memory for the buffer if it's not already allocated
 * and dynamically adjusts its size.
 *
 * Return: The number of characters read (excluding null terminator)on success,
 *         or -1 on failure.
 */
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t i = 0;
	char ch;

	initialize_buffer(lineptr, n);

	while (1)
	{
		if (i >= *n)
		{
			char *temp;
			*n += BUFFER_SIZE;
			temp = (char *)realloc(*lineptr, *n);
			if (temp == NULL)
			{
				perror("realloc");
				free(*lineptr);
				return (-1);
			}
			*lineptr = temp;
		}

		if (read(fileno(stream), &ch, 1) <= 0)
		{
			if (i == 0)
			{
				return (-1);
			}
			break;
		}

		(*lineptr)[i++] = ch;
		if (ch == '\n')
		{
			break;
		}
	}

	(*lineptr)[i] = '\0';
	return (i);
}
/**
 * print_environment - Prints the environment variables.
 *
 * This function iterates through the environment variables and prints each one
 * to the standard output (stdout).
 */
void print_environment(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
/**
 * my_exit - Exit the program with the specified status.
 * @status: The exit status to be returned by the program.
 *
 * This function ensures that all buffered data is flushed to stdout and stderr
 * before exiting the program using the _exit system call. This helps avoid any
 * issues with buffered output not being displayed.
 */
void my_exit(int status)
{
	fflush(stdout);
	fflush(stderr);

	_exit(status);
}
