#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "shell.h"
/**
 * cd_change_directory - this function changes the directory update environment
 *
 * @path: Directory path to change to
 */
void cd_change_directory(char *path)
{
	char new_path[1024];
	char *current_dir;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		perror("cd");
		return;
	}

	if (chdir(path) == -1)
	{
		perror("cd");
		free(current_dir);
		return;
	}

	if (setenv("PWD", getcwd(new_path, sizeof(new_path)), 1) == -1 ||
		getcwd(new_path, sizeof(new_path)) == NULL ||
		setenv("OLDPWD", current_dir, 1) == -1) {
		perror("cd");
		free(current_dir);
		return;
	}

	free(current_dir);
}
/**
 * cd_command - Builtin command cd
 * @path: Directory path
 */
void cd_command(char *path)
{
	char *home_dir;

	if (path == NULL)
	{
		home_dir = _getenviron("HOME");
		if (home_dir == NULL)
		{
			cd_change_directory(home_dir);
			return;
		}
		path = home_dir;
	}

	if (_strcmp(path, "-") == 0)
	{
		char *old_dir = _getenviron("OLDPWD");

		if (old_dir != NULL)
		{
			path = old_dir;
			printf("%s\n", path);
		} else
		{
			fprintf(stderr, "-: No previous directory\n");
			return;
		}
	}
	cd_change_directory(path);
}
