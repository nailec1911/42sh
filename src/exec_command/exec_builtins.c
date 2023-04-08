/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** exec_builtins
*/

#include <stddef.h>
#include "all_args.h"
#include "builtins/builtins_func.h"
#include "str_func.h"
#include "handle_input.h"
#include "macro_errors.h"

int exec_builtins(all_args_t *all_args, command_t to_exec)
{
    for (int i = 0; all_builtins[i].function != NULL; i += 1) {
        if (my_strcmp(to_exec.command[0], all_builtins[i].command) == 0) {
            return all_builtins[i].function(all_args, to_exec);
        }
    }
    return FAILURE;
}
