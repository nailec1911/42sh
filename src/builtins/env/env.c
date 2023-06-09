/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** env
*/

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include "str_func.h"
#include "mysh.h"
#include "macro_errors.h"

int do_env(mysh_t *mysh, command_t *to_exec)
{
    if (!mysh || !to_exec->args)
        return ERROR;
    if (to_exec->args[1] != NULL) {
        fprintf(stderr, "env: ‘%s’: No such file or directory\n",
                to_exec->args[1]);
        mysh->last_status = 127;
        return SUCCESS;
    }
    for (int i = 0; mysh->env[i]; ++i) {
        dprintf(to_exec->fd_out, "%s\n", mysh->env[i]);
    }
    mysh->last_status = 0;

    return SUCCESS;
}
