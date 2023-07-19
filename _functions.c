
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int _str_search(char *text, char key)
{
	long unsigned int i;
	for(i = 0 ; i < strlen(text); i++)
	{
		if(text[i] == key){
			return (1);
		}
	}
	return (0);
}

void execute_command(char *tokens[])
{
	pid_t pid = fork();
    	if (pid == -1) 
	{
		perror("fork");
		return;
	}
    	else if (pid == 0)
    	{
		char *path = getenv("PATH");
		char *dir = strtok(path,":");

		if (path == NULL) {
			fprintf(stderr, "PATH environment variable not set\n");
			exit(EXIT_FAILURE);
        	}
		if (_str_search(tokens[0], '/') != 0) {
            		if (execve(tokens[0], tokens, NULL) == -1) {
                		fprintf(stderr, "%s: Execution failed\n", tokens[0]);
                		exit(EXIT_FAILURE);
            		}
		}
		else
		{
			while (dir != NULL)
			{
				char *command_path;
				printf("================> %s\n",dir);
				/*char command_path[1000];
				snprintf(command_path, sizeof(command_path), "%s/%s", dir, tokens[0]);*/
				command_path = _strcat_path(dir ,tokens[0]);
				printf("this is command path : %s",command_path);
				if (access(command_path, X_OK) == 0) {
					if (execve(command_path, tokens, NULL) == -1) {
						fprintf(stderr, "%s: Execution failed\n", tokens[0]);
						exit(EXIT_FAILURE);
					}
				}
				dir = strtok(NULL, ":");
			}
		}
    	}
    	else
    	{
		int status;
	    	wait(&status);
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
