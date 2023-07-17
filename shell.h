#ifndef SHELL_H
#define SHELL_H

#include <sys/wait.h>

#define MAX_TOKENS 100

void execute_command(char *tokens[]);
void tokenize(char *buffer, char *tokens[], int *count);



#endif /* SHELL_H */