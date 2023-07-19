#include "shell.h"

char* my_strtok(char *str, const char *delim) {
    static char* token;
    static char* nextToken;
    char* result;

    if (str != NULL) {
        token = str;
    }

    if (token == NULL || *token == '\0') {
        return NULL;
    }

    result = token;
    nextToken = strpbrk(token, delim);

    if (nextToken != NULL) {
        *nextToken = '\0';
        token = nextToken + 1;
    } else {
        token += strlen(token);
    }

    return result;
}

int tokenize(char *buffer, char *tokens[]) {
    char *delim = " \n";
    int count = 0;
    char *token = my_strtok(buffer, delim);

    while (token != NULL && count < MAX_TOKENS) {
        tokens[count] = strdup(token);
        count++;
        token = my_strtok(NULL, delim);
    }

    tokens[count] = NULL;
    return count;
}

void freetok(char *tokens[], int count) {
    int i;
    for (i = 0; i < count; i++) {
        free(tokens[i]);
    }
}
