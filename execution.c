#include "shell.h"
/**
 * find_command_path - Find the full path of a command
 * in the PATH environment variable.
 *
 * @command_name: The name of the command to find.
 *
 * Return: A dynamically allocated string containing the full
 *         path of the command,or NULL if the command is not found.
 */
static char *find_command_path(const char *command_name)
{
	char *path = _getenviron("PATH");
	char *dir;
	char path_copy[1024];

	if (path == NULL)
	{
		write(STDERR_FILENO, "PATH environment variable not set\n", 34);
		return (NULL);
	}

	_strcpy(path_copy, path);

	dir = my_strtok(path_copy, ":");
	while (dir != NULL)
	{
		char temp_command_path[1024];
		size_t dir_len = _strlen(dir);

		_strcpy(temp_command_path, dir);
		temp_command_path[dir_len] = '/';
		_strcpy(temp_command_path + dir_len + 1, command_name);

		if (access(temp_command_path, X_OK) == 0)
		{
			return (_strdup(temp_command_path));
		}
		dir = my_strtok(NULL, ":");
	}

	return (NULL);
}
/**
 * execute_command_by_path - Execute a command given its full path.
 *
 * @command_path: The full path of the command to execute.
 * @tokens: An array of strings containing the command and its arguments.
 */
static void execute_command_by_path(const char *command_path, char *tokens[])
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (execve(command_path, tokens, NULL) == -1)
		{
			fprintf(stderr, "%s: Execution failed\n", tokens[0]);
			my_exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}
/**
 * execute_command - Execute a command from the shell.
 *
 * @tokens: An array of strings containing the command and its arguments.
 */
void execute_command(char *tokens[])
{
	char *command_path = tokens[0];
	int is_full_path = _str_search(tokens[0], '/') != NULL;

	if (!is_full_path)
	{
		if (_strcmp(tokens[0], "env") == 0)
		{
			print_environment();
			return;
		}

		command_path = find_command_path(tokens[0]);
		if (command_path == NULL)
		{
			fprintf(stderr, "%s: Command not found\n", tokens[0]);
			return;
		}
	}

	if (access(command_path, X_OK) != 0)
	{
	fprintf(stderr, "%s:Command not found path is:%s\n", tokens[0], command_path);
		return;
	}

	execute_command_by_path(command_path, tokens);

	if (!is_full_path)
		free(command_path);
}
