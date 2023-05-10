/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** init_mysh_env
*/

#include <builtins/env.h>
#include <stdlib.h>
#include <string.h>
#include "str_func.h"
#include "macro_errors.h"

char **init_mysh_env(char * const env[])
{
    int len = my_strstrlen(env);
    int sub_len = 0;
    char **result = malloc(sizeof(char*) * (len + 1));

    if (!env || !result || !env[0])
        return result;
    result[len] = NULL;
    for (int i = 0; i < len; i += 1) {
        sub_len = strlen(env[i]);
        result[i] = malloc(sizeof(char) * (sub_len + 1));
        if (result[i] == NULL)
            return NULL;
        result[i][sub_len] = '\0';
        for (int j = 0; j < sub_len; j += 1)
            result[i][j] = env[i][j];
    }
    return result;
}
