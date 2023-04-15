/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** unset_env
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"

static char **remove_from_env(char **env, int idx)
{
    int i = 0;
    int temp = 0;
    int len = my_strstrlen(env);
    char **result = malloc(sizeof(char *) * (len));

    result[len - 1] = NULL;

    for (; i < idx; ++i) result[i] = strdup(env[i]);

    temp = i + 1;
    for (; i < len - 1; ++i) {
        result[i] = strdup(env[temp]);
        temp++;
    }

    free_array(env);
    return result;
}

static int get_var_idx(char *env[], char *var)
{
    int len = strlen(var);
    for (int i = 0; env[i]; ++i) {
        if (strncmp(env[i], var, len) == 0)
            return i;
    }
    return -1;
}

int do_unsetenv(mysh_t *mysh, command_t to_exec)
{
    int idx = 0;

    if (to_exec.command[1] == NULL) {
        fprintf(stderr, "unsetenv; Too few arguments.\n");
        mysh->last_status = 1;
        return SUCCESS;
    }
    for (int i = 1; to_exec.command[i] != NULL; i += 1) {
        idx = get_var_idx(mysh->env, to_exec.command[i]);
        if (idx != -1)
            mysh->env = remove_from_env(mysh->env, idx);
    }
    return SUCCESS;
}
