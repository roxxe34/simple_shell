#include <stdio.h>
#include <stdlib.h>

int get_line(char **buffer, size_t *len) {
    printf("$ ");

    ssize_t read = getline(buffer, len, stdin);
    if (read == -1 || read == EOF) {
        free(*buffer);
        return 0;
    }
    

    // Remove the trailing newline character
    if ((*buffer)[read - 1] == '\n') {
        (*buffer)[read - 1] = '\0';
    }

    return 1;
}
