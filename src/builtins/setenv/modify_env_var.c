/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** modify_env_var
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "builtins/env.h"
#include "mysh.h"
#include "str_func.h"
#include "macro_errors.h"

static char *edit_var(char *to_change, char *new_value)
{
    int i = 0;
    char *result = NULL;

    if (new_value == NULL)
        return my_strcat_dup(to_change, "=");

    for (; to_change[i] != '\0' && to_change[i] != '='; ++i);

    if ((result = malloc(sizeof(char) * (i + 1))) == NULL)
        return NULL;

    result[i] = '\0';

    for (int j = 0; j < i; ++j) result[i] = to_change[i];

    if ((result = my_strcat_with_char(to_change, new_value, '=')) == NULL)
        return NULL;
    return result;
}

static char **add_var(char **env, char *to_change, char *new_value, int len)
{
    char **new_env = malloc(sizeof(char*) * (len + 2));
    new_env[len + 1] = NULL;

    if (new_value == NULL)
        new_value = "";

    for (int i = 0; i < len; i += 1) {
        new_env[i] = malloc(sizeof(char) * (my_strlen(env[i]) + 1));
        new_env[i][my_strlen(env[i])] = '\0';

        for (int j = 0; j < my_strlen(env[i]); j += 1) {
            new_env[i][j] = env[i][j];
        }
    }
    new_env[len] = my_strcat_with_char(to_change, new_value, '=');
    free_array(env);
    return new_env;
}

static char **init_env(char *to_change, char *new_value)
{
    to_change = my_strcat_with_char(to_change, new_value, '=');
    int len = strlen(to_change);
    char **env = (char**) malloc(2 * sizeof(char));
    if (env == NULL)
        return NULL;
    env[0] = malloc(sizeof(char) * (len + 1));
    if (env[0] == NULL)
        return NULL;

    for (int i = 0; i < len; ++i)
        env[0][i] = to_change[i];

    free(to_change);
    return env;
}

int modify_env_var(char *to_change, mysh_t *mysh, char *new_value)
{
    int len = strlen(to_change);
    int i = 0;

    for (; mysh->env[i] != NULL; ++i) {
        if (strncmp(mysh->env[i], to_change, len) == 0) {
            mysh->env[i] = edit_var(to_change, new_value);
            return SUCCESS;
        }
    }
    if (i == 0) {
        if ((mysh->env = init_env(to_change, new_value)) == NULL)
            return ERROR;
        return SUCCESS;
    }
    if ((mysh->env = add_var(mysh->env, to_change, new_value, i)) == NULL)
        return ERROR;
    return SUCCESS;
}
