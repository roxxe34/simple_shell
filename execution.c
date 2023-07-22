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
		print(shell_name, STDERR_FILENO);
		print(": 1", STDERR_FILENO);
		print(path, STDERR_FILENO);
		print(": PATH environment variable not set\n", STDERR_FILENO);
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
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tokens[0], STDERR_FILENO);
		print(": Execution failed\n", STDERR_FILENO);
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

		if (_strcmp(tokens[0], "unsetenv") == 0) {
        	unset_environment_variable(tokens[1]);
			return;
    	}

		if (_strcmp(tokens[0], "setenv") == 0) {
        	set_environment_variable(tokens[1], tokens[2]);
			return;
		}

		command_path = find_command_path(tokens[0]);
		if (command_path == NULL)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1: ", STDERR_FILENO);
			print(tokens[0], STDERR_FILENO);
			print(": Command not found\n", STDERR_FILENO);
			return;
		}
	}

	if (access(command_path, X_OK) != 0)
	{
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tokens[0], STDERR_FILENO);
		print(": Command not found path is:", STDERR_FILENO);
		print(command_path, STDERR_FILENO);
		return;
	}

	execute_command_by_path(command_path, tokens);

	if (!is_full_path)
		free(command_path);
}
