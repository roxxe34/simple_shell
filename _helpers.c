#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

char *_getenviron(char *env_var)
{
    extern char **environ;
    int i = 0;
    char *tok;

    while(environ[i])
    {
        tok = strtok(environ[i], "=");
        if(_strcmp(env_var, tok) == 0)
            return (strtok(NULL, "\n"));
        i++;
    }
    return (NULL);
}

char *_strcat_path(char *dest, char *src)
{
    char *s = dest;

    while (*dest != '\0')
    {
	    dest++;
    }

    if(*(dest-1)!='/'){
   	*dest = '/';
    	dest++; 
    }
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    printf("this is the resut : %s",s);
    return (s);
}
