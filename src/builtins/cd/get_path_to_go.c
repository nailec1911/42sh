/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** get_path
*/

#include <stddef.h>
#include "str_func.h"
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"

static char *get_home_path(all_args_t *all_args)
{
    char *home_path = get_env_var(all_args->list_env, "HOME=");
    char *new_path;

    if (home_path == NULL) {
        my_putstr("cd: No home directory.\n", 2);
        all_args->last_status = 1;
        return NULL;
    }
    if (all_args->command[1] == NULL)
        return home_path;
    if ((new_path =
    my_strcat_dup(home_path, all_args->command[1] + 1)) == NULL) {
        all_args->last_status = FAILURE;
        return NULL;
    }
    return new_path;
}

char *get_path_to_go(all_args_t *all_args)
{
    char *path = all_args->command[1];

    if (all_args->command[1] == NULL || all_args->command[1][0] == '~')
        return get_home_path(all_args);
    if (all_args->command[1][0] == '-' && all_args->command[1][1] == '\0')
        path = get_env_var(all_args->list_env, "OLDPWD=");
    if (path == NULL) {
        my_putstr(": No such file or directory.\n", 2);
        all_args->last_status = 1;
    }
    return path;
}
