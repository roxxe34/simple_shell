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

void execute_command(char *tokens[]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    } else if (pid == 0) 
    {
        int is_full_path = _str_search(tokens[0], '/') != 0;

        if (is_full_path) {
            
            if (execve(tokens[0], tokens, NULL) == -1) {
                write(STDERR_FILENO, tokens[0], _strlen(tokens[0]));
                write(STDERR_FILENO, ": Execution failed\n", 18);
                exit(EXIT_FAILURE);
            }
        } else {
        
            char *path = _getenviron("PATH");
            char *dir = strtok(path, ":");

            if (path == NULL) {
                write(STDERR_FILENO, "PATH environment variable not set\n", 34);
                exit(EXIT_FAILURE);
            }

            while (dir != NULL) {
                char command_path[1024];
                size_t dir_len = _strlen(dir);
                size_t token_len = _strlen(tokens[0]);
                _strcpy(command_path, dir);
                 command_path[dir_len] = '/';
                _strcpy(command_path + dir_len + 1, tokens[0]);

                if (access(command_path, X_OK) == 0) {
                    if (execve(command_path, tokens, NULL) == -1) {
                        write(STDERR_FILENO, tokens[0], token_len);
                        write(STDERR_FILENO, ": Execution failed\n", 18);
                        exit(EXIT_FAILURE);
                    }
                }
                dir = strtok(NULL, ":");
            }
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