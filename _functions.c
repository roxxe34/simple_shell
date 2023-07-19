#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int _str_search(char *text, char key)
{
	int i;
	for(i = 0 ; i < _strlen(text); i++)
	{
		if(text[i] == key){
			return (1);
		}
	}
	return (0);
}

void execute_command(char* tokens[]) {
    int is_full_path = strchr(tokens[0], '/') != NULL;
    char* command_path = tokens[0];
    pid_t pid;
    if (!is_full_path) {
        char* path = getenv("PATH");
        char* dir = strtok(path, ":");

        if (path == NULL) {
            write(STDERR_FILENO, "PATH environment variable not set\n", 34);
            return;
        }

        while (dir != NULL) {
            char temp_command_path[1024];
            size_t dir_len = strlen(dir);
            
            strcpy(temp_command_path, dir);
            temp_command_path[dir_len] = '/';
            strcpy(temp_command_path + dir_len + 1, tokens[0]);

            if (access(temp_command_path, X_OK) == 0) {
                command_path = temp_command_path;
                break;
            }
            dir = strtok(NULL, ":");
        }
    }

    if (access(command_path, X_OK) != 0) {
        fprintf(stderr, "%s: Command not found\n", tokens[0]);
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
            exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}
int tokenize(char *buffer, char *tokens[])
{
    	char *delim = " \n";
    	int count = 0;

    	char *token = strtok(buffer, delim);
    	while (token != NULL && count < MAX_TOKENS) {
        	tokens[count] = strdup(token);
        	count++;
        	token = strtok(NULL, delim);
    	}

    	tokens[count] = NULL;
    	return count;
}

int _strcmp(char *s1, char *s2)
{
    	while (*s1 && *s2) {
        	if (*s1 != *s2) {
            		return *s1 - *s2;
        	}
        	s1++;
        	s2++;
    	}
    	return *s1 - *s2;
}
void freetok(char *tokens[], int count)
{
	int i;
    	for (i = 0; i < count; i++) 
        	{
        		free(tokens[i]);
         	}
}