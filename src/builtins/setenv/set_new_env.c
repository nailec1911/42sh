/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** set_new_env
*/

#include <stdlib.h>
#include "list_env.h"

static int size_malloc(env_var_t *list)
{
    env_var_t *temp = list;
    int len = 0;

    for (; temp != NULL; temp = temp->next)
        len += 1;
    return len;
}

char **set_new_env(env_var_t *env_list)
{
    int len_malloc = size_malloc(env_list) + 1;
    char **new_env = NULL;
    int i = 0;

    if ((new_env = malloc(sizeof(char *) * (len_malloc))) == NULL)
        return NULL;
    for (int i = 0; i < len_malloc; i += 1)
        new_env[i] = NULL;
    while (env_list != NULL) {
        new_env[i] = env_list->var;
        if (new_env[i] == NULL)
            return NULL;
        env_list = env_list->next;
        i += 1;
    }
    return new_env;
}
