/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** create_list_env
*/

#include <stddef.h>
#include <builtins/env.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

static int get_strstr_len(char * const env[])
{
    int len = 0;
    for (int i = 0; env[i] != NULL; i += 1)
        len += 1;
    return len;
}

char **init_mysh_env(char * const env[])
{
    int len = get_strstr_len(env);
    int sub_len = 0;

    char **result = malloc(sizeof(char*) * (len + 1));
    result[len] = NULL;

    for (int i = 0; i < len; i += 1) {
        sub_len = strlen(env[i]);
        result[i] = malloc(sizeof(char) * (sub_len + 1));
        result[i][sub_len] = '\0';
        for (int j = 0; j < sub_len; j += 1)
            result[i][j] = env[i][j];
    }
    return result;
}
