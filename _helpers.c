#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"


char* _getenviron(char* name) {
    extern char** environ;
     size_t name_len = _strlen(name);
     int i;

    if (name == NULL || _strlen(name) == 0) {
        return NULL;
    }

    

    for (i = 0; environ[i] != NULL; i++) {
        if (my_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=') {
            return environ[i] + name_len + 1;
        }
    }

    return NULL;
}
int my_strncmp(const char* str1, const char* str2, size_t n) {
    size_t i;
    for (i = 0; i < n; i++) 
    {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        } else if (str1[i] == '0') {
            return 0;
        }
    }
    return 0;
}
int _strlen(char *str)
{   
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return (len);

}

char *_strcpy(char *dest, char *src)
{
	int a;

	for (a = 0; src[a] != '\0'; a++)
		dest[a] = src[a];
	dest[a] = '\0';
	return (dest);
}

