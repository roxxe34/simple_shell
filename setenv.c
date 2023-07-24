#include "shell.h"
/**
 * set_environment_variable - se environment variable
 * @variable: The name of the variable
 * @value: The value of the to variable
 */
void set_environment_variable(const char* variable, const char* value) {
    if (variable == NULL || value == NULL) {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return;
    }
	if (setenv(variable, value, 1) == 0) {
        printf("Environment variable set successfully.\n");
    } else {
        perror("Error setting environment variable");
    }
}
/**
 * unset_environment_variable - unset environment variable
 * @variable: The name of the variable
 */
void unset_environment_variable(const char* variable) {
    if (variable == NULL) {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return;
    }
	if (unsetenv(variable) == 0) {
        printf("Environment variable unset successfully.\n");
    } else {
        perror("Error unsetting environment variable");
    }
}