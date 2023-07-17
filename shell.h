#ifndef MAIN_H
#define MAIN_H

#include <sys/wait.h>

#define MAX_TOKENS 100

void execute_command(char *tokens[]);
void tokenize(char *buffer, char *tokens[], int *count);



#endif
