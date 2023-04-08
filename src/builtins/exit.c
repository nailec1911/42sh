/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** exit
*/

#include <stddef.h>
#include "all_args.h"
#include "str_func.h"
#include "macro_errors.h"

int do_exit(all_args_t *all_args, command_t to_exec)
{
    if (to_exec.command[1] != NULL) {
        my_putstr("exit: Expression Syntax.\n", 2);
        all_args->last_status = 1;
        return SUCCESS;
    }
    return EXIT;
}
