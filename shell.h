#ifndef SHELL_H
#define SHELL_H

#include <sys/wait.h>

#define MAX_TOKENS 100

int tokenize(char *buffer, char *tokens[]);
void execute_command(char *tokens[]);
int _strcmp(char *s1, char *s2);
void freetok(char *tokens[]);

#endif /* SHELL_H */
