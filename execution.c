#include "shell.h"

/**
 * find_command_path - Find the full path of a command
 * in the PATH environment variable.
 *
 * @command_name: The name of the command to find.
 *
 * Return: A dynamically allocated string containing the full
 *		 path of the command,or NULL if the command is not found.
 */
static char *find_command_path(const char *command_name)
{
	 char *path = _getenviron("PATH");
	char *dir;
	char path_copy[1024];


	char *special_value;

	special_value = get_special_value(command_name);
	if (special_value != NULL)
		return (special_value);


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
 * handle_builtin_command - Handle built-in shell commands.
 * @tokens: An array of strings containing the command and its arguments.
 *
 */
void handle_builtin_command(char *tokens[])
{
	int i;

	if (_strcmp(tokens[0], "env") == 0)
	{
		print_environment();
	}
	else if (_strcmp(tokens[0], "cd") == 0)
	{
		cd_command(tokens[1]);
	}
	else if (_strcmp(tokens[0], "setenv") == 0)
	{
		set_environment_variable(tokens[1], tokens[2]);
		return;
	}
	else if (_strcmp(tokens[0], "unsetenv") == 0)
	{
        	unset_environment_variable(tokens[1]);
			return;
    }
	else if (_strcmp(tokens[0], "echo") == 0)
	{
		for (i = 1; tokens[i] != NULL; i++)
		{
			char *arg = tokens[i];
			char *special_value = get_special_value(arg);

			if (special_value != NULL)
			{
				print_special_value(arg, STDOUT_FILENO);
			}
			else
			{
				print(arg, STDOUT_FILENO);
			}

			if (tokens[i + 1] != NULL)
				print(" ", STDOUT_FILENO);
		}
		print("\n", STDOUT_FILENO);
	}
}
/**
 * execute_external_command - Execute an external command.
 * @tokens: An array of strings containing the command and its arguments.
 *
 */
void execute_external_command(char *tokens[])
{
	char *command_path;
	int is_full_path;

	command_path = tokens[0];
	is_full_path = _str_search(tokens[0], '/') != NULL;

	if (!is_full_path)
	{
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
/**
 * execute_command - Execute a shell command.
 * @tokens: An array of strings containing the command and its arguments.
 */
void execute_command(char *tokens[])
{
	if (_strcmp(tokens[0], "env") == 0 ||
		_strcmp(tokens[0], "cd") == 0 ||
		_strcmp(tokens[0], "echo") == 0 ||
		_strcmp(tokens[0], "setenv") == 0 ||
		_strcmp(tokens[0], "unsetenv") == 0 )
	{
		handle_builtin_command(tokens);
	}
	else
	{
		execute_external_command(tokens);
	}
}
