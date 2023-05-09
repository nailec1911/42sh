/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** get_path
*/

#include <stddef.h>
#include <stdio.h>
#include "str_func.h"
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"

static char *get_home_path(mysh_t *mysh, command_t *to_exec)
{
    char *home_path = get_env_var(mysh, "HOME=");
    char *new_path;

    if (home_path == NULL) {
        fprintf(stderr, "cd: No home directory.\n");
        mysh->last_status = 1;
        return NULL;
    }
    if (to_exec->args[1] == NULL)
        return home_path;
    new_path = my_strcat_dup(home_path, to_exec->args[1] + 1);
    if (new_path == NULL) {
        mysh->last_status = FAILURE;
        return NULL;
    }
    return new_path;
}

char *get_path_to_go(mysh_t *mysh, command_t *to_exec)
{
    char *path = to_exec->args[1];

    if (to_exec->args[1] == NULL || to_exec->args[1][0] == '~')
        return get_home_path(mysh, to_exec);
    if (to_exec->args[1][0] == '-' && to_exec->args[1][1] == '\0') {
        path = get_env_var(mysh, "OLDPWD=");
    }
    if (path == NULL) {
        fprintf(stderr, ": No such file or directory.\n");
        mysh->last_status = 1;
    }
    return path;
}
