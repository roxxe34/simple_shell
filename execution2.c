#include "shell.h"
/**
 * get_process_id - Get the process ID as a string.
 *
 * Return: A pointer to a newly allocated string containing the process ID,
 *         or NULL if an error occurs.
 */
char *get_process_id()
{
	int pid = getpid();
	int num_digits = 0;
	int temp = pid;
	char *value;

	while (temp != 0)
	{
		num_digits++;
		temp /= 10;
	}

	value = (char *)malloc(num_digits + 1);

	if (value != NULL)
	{
		int index = num_digits;

		value[index] = '\0';

		while (index > 0)
		{
			value[--index] = '0' + (pid % 10);
			pid /= 10;
		}
	}

	return (value);
}
/**
 * get_environment_value - Get the value of an env variable or special value
 * @variable: The input variable string starting with '$'.
 *
 * Return: A pointer to a newly allocated string containing the value of the
 *         environment variable or special value, or NULL if the variable
 *         is not found or an error occurs.
 */
char *get_environment_value(const char *variable)
{
	char *value = NULL;

	if (variable[0] == '$')
	{
		char *var_copy = _strdup(variable);
		char *arg = my_strtok(var_copy, "$");

		if (arg == NULL)
		{
			free(var_copy);
			return (NULL);
		}

		if (_strcmp(arg, "?") == 0)
		{
			value = _strdup("0");
		}
		else
		{
			value = _getenviron(arg);
			if (value)
				value = _strdup(value);
		}

		free(var_copy);
	}

	return (value);
}
/**
 * get_special_value - Get the value of a special value or env variable.
 * @variable: The input variable string.
 *
 * Return: A pointer to a newly allocated string containing the value of the
 *         special value or environment variable, or NULL if
 *         the variable is not found or an error occurs.
 */
char *get_special_value(const char *variable)
{
	char *value = NULL;

	if (_strcmp(variable, "$$") == 0)
	{
		value = get_process_id();
	}
	else
	{
		value = get_environment_value(variable);
	}

	return (value);
}
/**
 * print_special_value - Print the value of a special value or envi variable.
 * @variable: The input variable string.
 * @fd: The file descriptor to write the value to.
 *
 * Return: None.
 */
void print_special_value(const char *variable, int fd)
{
	if (_strcmp(variable, "$$") == 0)
	{
		pid_t pid = getpid();
		char pid_str[12];
		int num_digits = 0;
		int temp = pid;

		while (temp != 0)
		{
			num_digits++;
			temp /= 10;
		}

		pid_str[num_digits] = '\0';

		while (num_digits > 0)
		{
			pid_str[--num_digits] = '0' + (pid % 10);
			pid /= 10;
		}

		print(pid_str, fd);
	}
	else
	{
		char *special_value = get_special_value(variable);


		if (special_value != NULL)
		{
			print(special_value, fd);
			free(special_value);
		}
	}
}
