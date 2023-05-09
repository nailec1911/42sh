/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** exit
*/

#include <stddef.h>
#include <stdio.h>
#include "mysh.h"
#include "str_func.h"
#include "macro_errors.h"

int do_exit(mysh_t *mysh, command_t *to_exec)
{
    if (!mysh || !to_exec)
        return ERROR;
    if (to_exec->args[1] != NULL) {
        fprintf(stderr, "exit: Expression Syntax.\n");
        mysh->last_status = 1;
        return SUCCESS;
    }
    return EXIT;
}
