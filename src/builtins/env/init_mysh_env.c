/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** init_mysh_env
*/

#include <stddef.h>
#include <builtins/env.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_errors.h"

static int get_strstr_len(char * const env[])
{
    int len = 0;

    if (env == NULL)
        return 0;
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
    if (env == NULL)
        return result;
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
