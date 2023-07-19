#ifndef SHELL_H
#define SHELL_H

#include <sys/wait.h>

#define MAX_TOKENS 100

int tokenize(char *buffer, char *tokens[]);
void execute_command(char *tokens[]);
int _strcmp(char *s1, char *s2);
void freetok(char *tokens[], int count);
char* _getenviron(char* name);
int my_strncmp(const char* str1, const char* str2, size_t n);
int _strlen(char *str);
char *_strcpy(char *dest, char *src);

#endif /* SHELL_H */
