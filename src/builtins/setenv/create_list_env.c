/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** create_list_env
*/

#include <stddef.h>
#include <builtins/env.h>
#include "list_env.h"
#include "macro_errors.h"

env_var_t *create_list_env(char * const env[])
{
    env_var_t *list = NULL;
    char *to_add;
    int i = 0;

    if (env == NULL || env[0] == NULL)
        return NULL;
    while (env[i] != NULL){
        to_add = my_str_dup(env[i]);
        if (put_elt_in_list(&list, to_add) == ERROR)
            return NULL;
        i = i + 1;
    }
    return list;
}
