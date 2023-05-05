/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** find_in_env
*/

#include <string.h>

char *find_in_env(char **env, char *name)
{
    for (int i = 0; env[i] != NULL; i += 1)
        if (strncmp(env[i], name, strlen(name)) == 0)
            return &env[i][strlen(name)];
    return NULL;
}
