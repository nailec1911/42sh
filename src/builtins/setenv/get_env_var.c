/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** get_env_var
*/

#include <stddef.h>
#include "list_env.h"
#include "macro_errors.h"
#include "str_func.h"

char *get_env_var(env_var_t *list_env, char *var)
{
    int i = 0;
    int len_var = my_strlen(var);

    for (; list_env != NULL; i += 1) {
        if (my_strncmp(var, list_env->var, len_var) == SUCCESS)
            return list_env->var + len_var;
        list_env = list_env->next;
    }
    return NULL;
}
