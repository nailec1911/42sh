/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** setenv
*/

#include <stddef.h>
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"

static int check_args(char **command)
{
    if (command[1] == NULL)
        return SUCCESS;
    if (command[2] != NULL && command[3] != NULL) {
        my_putstr("setenv: Too many arguments.\n", 2);
        return FAILURE;
    }
    if (str_is_alphanum(command[1]) != SUCCESS) {
        my_putstr
        ("setenv: Variable name must contain alphanumeric characters.\n", 2);
        return FAILURE;
    }
    return SUCCESS;
}

int do_setenv(all_args_t *all_args, command_t to_exec)
{
    if (check_args(to_exec.command) != SUCCESS) {
        all_args->last_status = 1;
        return SUCCESS;
    }
    if (all_args->command[1] == NULL || all_args->command[1][0] == '\0')
        return do_env(all_args, to_exec);
    if (modify_env_var
    (to_exec.command[1], all_args, to_exec.command[2]) == ERROR)
        return ERROR;
    all_args->last_status = 0;
    return SUCCESS;
}
