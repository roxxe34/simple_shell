#ifndef SHELL_H
#define SHELL_H

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define BUFFER_SIZE 1024

int is_number(const char* str);
char* my_strtok(char *str, const char *delim);
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);
void print_environment();
void my_exit(int status);
int _str_search(const char *text, char key);
void execute_command(char *tokens[]);
int tokenize(char *buffer, char *tokens[]);
int _strcmp(const char *s1, const char *s2);
void freetok(char *tokens[], int count);
char* _getenviron(const char* name);
int my_strncmp(const char* str1, const char* str2, size_t n);
int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);

#endif