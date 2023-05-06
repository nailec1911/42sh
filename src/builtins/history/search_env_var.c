/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <string.h>
#include "macro_errors.h"
#include "str_func.h"
#include <unistd.h>
#include <pwd.h>

char *find_in_env(char **env, char *name)
{
    if (env == NULL || name == NULL)
        return NULL;
    for (int i = 0; env[i] != NULL; i += 1)
        if (strncmp(env[i], name, strlen(name)) == 0)
            return &env[i][strlen(name)];
    return NULL;
}

char *get_path_home(char *filepath)
{
    char *home = NULL;
    struct passwd *pwd;

    if (filepath == NULL)
        return NULL;
    pwd = getpwuid(getuid());
    home = my_strcat_dup(pwd->pw_dir, filepath);
    if (home == NULL)
        return NULL;
    return home;
}
