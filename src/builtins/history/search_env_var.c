/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <string.h>
#include "macro_errors.h"
#include "str_func.h"

char *find_in_env(char **env, char *name)
{
    for (int i = 0; env[i] != NULL; i += 1)
        if (strncmp(env[i], name, strlen(name)) == 0)
            return &env[i][strlen(name)];
    return NULL;
}

char *get_path_home(char *to, char **env)
{
    char *home = NULL;
    char *path = NULL;

    if ((home = find_in_env(env, "HOME=")) == NULL)
        return NULL;
    if ((path = my_strcat_dup(home, to)) == NULL)
        return NULL;
    return path;
}
