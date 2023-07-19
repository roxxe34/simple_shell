#include "shell.h"

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream) {
    size_t i = 0;
    char ch;

    if (*lineptr == NULL || *n == 0) {
        *n = BUFFER_SIZE;
        *lineptr = (char *)malloc(*n);
        if (*lineptr == NULL) {
            perror("malloc");
            return -1;
        }
    }

    while (1) {
        if (i >= *n) {
            char *temp;
            *n += BUFFER_SIZE;
            temp = (char *)realloc(*lineptr, *n);
            if (temp == NULL) {
                perror("realloc");
                free(*lineptr);
                return -1;
            }
            *lineptr = temp;
        }

        if (read(fileno(stream), &ch, 1) <= 0) {
            if (i == 0) {
                return -1;
            }
            break;
        }

        (*lineptr)[i++] = ch;
        if (ch == '\n') {
            break;
        }
    }

    (*lineptr)[i] = '\0';
    return i;
}

void print_environment() {
    extern char** environ;
    int i;

    for (i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}

void my_exit(int status) {
    fflush(stdout);
    fflush(stderr);

    _exit(status);
}
