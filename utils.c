#include "shell.h"

int is_number(const char* str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int _str_search(const char *text, char key) {
    int i;
    for (i=0; text[i] != '\0'; i++) {
        if (text[i] == key) {
            return 1;
        }
    }
    return 0;
}

int _strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char *_strcpy(char *dest, const char *src) {
    int a;

    for (a = 0; src[a] != '\0'; a++) {
        dest[a] = src[a];
    }
    dest[a] = '\0';
    return dest;
}

int my_strncmp(const char* str1, const char* str2, size_t n) {
    size_t i;
    for (i=0; i < n; i++) {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        } else if (str1[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

int _strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}


char* _getenviron(const char* name) {
    extern char** environ;
    int i;
    size_t name_len = _strlen(name);

    if (name == NULL || name_len == 0) {
        return NULL;
    }

    for (i = 0; environ[i] != NULL; i++) {
        if (my_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=') {
            return environ[i] + name_len + 1;
        }
    }

    return NULL;
}