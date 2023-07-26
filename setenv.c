#include "shell.h"
/**
 * set_environment_variable - se environment variable
 * @variable: The name of the variable
 * @value: The value of the to variable
 */
int environ_size() {
    char** env = environ;
    int size = 0;
    while (*env != NULL) {
        size++;
        env++;
    }
    return size;
}
int custom_putenv(const char* env_var)
{
	char* var_name;
	char* equal_sign;
	char** env;
	char** new_environ;
	int i = 0;

    if (env_var == NULL) {
		write_str_to_stderr("Error: Invalid argument\n");
        return -1;
    }

    var_name = _strdup(env_var);
    equal_sign = my_strchr(var_name, '=');

    if (equal_sign == NULL || equal_sign == var_name) {
		write_str_to_stderr("Error: Invalid environment variable format\n");
        free(var_name);
        return -1;
    }

    *equal_sign = '\0';

    env = environ;
    while (*env != NULL) {
        if (_strcmp(*env, var_name) == 0) {
            *env = _strdup(env_var);
            free(var_name);
            return 0;
        }
        env++;
    }

    new_environ = (char**)malloc((environ_size() + 2) * sizeof(char*));
    if (new_environ == NULL) {
		write_str_to_stderr("Error: Memory allocation failed\n");
        free(var_name);
        return -1;
    }

    env = environ;
    
    while (*env != NULL) {
        new_environ[i] = *env;
        env++;
        i++;
    }

    new_environ[i] = _strdup(env_var);
    new_environ[i + 1] = NULL;

    environ = new_environ;

    free(var_name);
    return 0;
}
int set_env(const char* variable, const char* value, int overwrite) 
{
	size_t variable_len;
	size_t value_len;
	size_t total_len;
	size_t i;
	char* env_var;
	int result;

    if (variable == NULL || value == NULL) {
		write_str_to_stderr("Error: Invalid arguments\n");
        return -1;
    }

    if (!overwrite && _getenviron(variable) != NULL) {
        return 0;
    }

    variable_len = _strlen(variable);
     value_len = _strlen(value);
    total_len = variable_len + value_len + 2;

    env_var = (char*)malloc(total_len);
    if (env_var == NULL) {
		write_str_to_stderr("Error: Memory allocation failed\n");
        return -1;
    }

    for (i = 0; i < variable_len; ++i) {
        env_var[i] = variable[i];
    }
    env_var[variable_len] = '=';
    for (i = 0; i < value_len; ++i) {
        env_var[variable_len + 1 + i] = value[i];
    }
    env_var[total_len - 1] = '\0';

    result = custom_putenv(env_var);
    if (result != 0) {
		write_str_to_stderr("Error: Failed to set environment variable\n");
    }

    return result;
}

int unset_env(const char *name)
{
	size_t name_len;
	char **env;
	char **next;

    if (name == NULL || name[0] == '\0' || my_strchr(name, '=') != NULL)
    {
        return -1;
    }

    name_len = _strlen(name);
    for (env = environ; *env != NULL; env++)
    {
        if (my_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
        {
            for (next = env + 1; *next != NULL; env++, next++)
            {
                *env = *next;
            }
            return 0;
        }
    }

    return 0;
}
void set_environment_variable(const char *variable, const char *value)
{
	if (variable == NULL || value == NULL)
	{
		write_str_to_stderr("Usage: setenv VARIABLE VALUE\n");
		return;
	}
	if (set_env(variable, value, 1) == 0)
	{
		printf("Environment variable set successfully.\n");
	} else
	{
		write_str_to_stderr("Error setting environment variable");
	}
}
/**
 * unset_environment_variable - unset environment variable
 * @variable: The name of the variable
 */
void unset_environment_variable(const char *variable)
{
	if (variable == NULL)
	{
		write_str_to_stderr("Usage: unsetenv VARIABLE\n");
		return;
	}
	if (unset_env(variable) == 0)
	{
		printf("Environment variable unset successfully.\n");
	} else
	{
		write_str_to_stderr("Error unsetting environment variable\n");
	}
}
