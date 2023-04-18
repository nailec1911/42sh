/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** setenv
*/

#include <stddef.h>
#include <stdio.h>
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"

static int check_args(char **command)
{
    if (command[1] == NULL)
        return SUCCESS;
    if (command[2] != NULL && command[3] != NULL) {
        fprintf(stderr, "setenv: Too many arguments.\n");
        return FAILURE;
    }
    if (str_is_alphanum(command[1]) != SUCCESS) {
        fprintf(stderr,
        "setenv: Variable name must contain alphanumeric characters.\n");
        return FAILURE;
    }
    return SUCCESS;
}

int do_setenv(mysh_t *mysh, command_t to_exec)
{
    if (check_args(to_exec.command) != SUCCESS) {
        mysh->last_status = 1;
        return SUCCESS;
    }
    if (mysh->command[1] == NULL || mysh->command[1][0] == '\0')
        return do_env(mysh, to_exec);
    if (modify_env_var
    (to_exec.command[1], mysh, to_exec.command[2]) == ERROR)
        return ERROR;
    mysh->last_status = 0;
    return SUCCESS;
}
