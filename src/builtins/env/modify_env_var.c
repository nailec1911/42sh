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

static int edit_var(char *to_change, char *new_value, char **old)
{
    free(*old);
    if (new_value == NULL) {
        if ((*old = my_strcat_dup(to_change, "=")) == NULL)
            return ERROR;
        return SUCCESS;
    }
    if ((*old = my_strcat_with_char(to_change, new_value, '=')) == NULL)
        return ERROR;
    return SUCCESS;
}

static char **add_var(char **env, char *to_change, char *new_value, int len)
{
    char **new_env = malloc(sizeof(char*) * (len + 2));

    if (new_env == NULL)
        return NULL;
    new_env[len + 1] = NULL;
    if (new_value == NULL)
        new_value = "";
    for (int i = 0; i < len; ++i)
        new_env[i] = env[i];
    new_env[len] = my_strcat_with_char(to_change, new_value, '=');
    if (new_env[len] == NULL)
        return NULL;
    free(env);
    return new_env;
}

static char **init_var(char *to_change, char *new_value)
{
    char **env = malloc(2 * sizeof(char *));
    int len = 0;

    to_change = my_strcat_with_char(to_change, new_value, '=');
    len = strlen(to_change);
    if (env == NULL || to_change == NULL)
        return NULL;
    if ((env[0] = malloc(sizeof(char) * (len + 1))) == NULL)
        return NULL;
    for (int i = 0; i < len; ++i)
        env[0][i] = to_change[i];
    free(to_change);
    return env;
}

int modify_env_var(char *to_change, mysh_t *mysh, char *new_value)
{
    int len = 0;
    int i = 0;

    if (!to_change || !mysh || !mysh->env)
        return ERROR;
    len = strlen(to_change);
    for (; mysh->env[i] != NULL; ++i) {
        if (strncmp(mysh->env[i], to_change, len) == 0)
            return edit_var(to_change, new_value, &(mysh->env[i]));
    }
    if (i == 0) {
        if ((mysh->env = init_var(to_change, new_value)) == NULL)
            return ERROR;
        return SUCCESS;
    }
    if ((mysh->env = add_var(mysh->env, to_change, new_value, i)) == NULL)
        return ERROR;
    return SUCCESS;
}
