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
