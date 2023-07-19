#include "shell.h"

void execute_command(char *tokens[]) {
    char *command_path = tokens[0];
    int is_full_path = strchr(tokens[0], '/') != NULL;
    pid_t pid;

    if (!is_full_path) {
        char *path = getenv("PATH");
        char *dir;
        char path_copy[1024];

        if (path == NULL) {
            write(STDERR_FILENO, "PATH environment variable not set\n", 34);
            return;
        }

        if (_strcmp(tokens[0], "env") == 0) {
            print_environment();
            return;
        }

        _strcpy(path_copy, path);

        dir = strtok(path_copy, ":");
        while (dir != NULL) {
            char temp_command_path[1024];
            size_t dir_len = _strlen(dir);

            _strcpy(temp_command_path, dir);
            temp_command_path[dir_len] = '/';
            _strcpy(temp_command_path + dir_len + 1, tokens[0]);

            if (access(temp_command_path, X_OK) == 0) {
                command_path = temp_command_path;
                break;
            }
            dir = strtok(NULL, ":");
        }
    }

    if (access(command_path, X_OK) != 0) {
        fprintf(stderr, "%s: Command not found\ncommand_path variable is: %s\n", tokens[0], command_path);
        return;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        if (execve(command_path, tokens, NULL) == -1) {
            fprintf(stderr, "%s: Execution failed\n", tokens[0]);
            my_exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}
