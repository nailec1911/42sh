/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** exec_builtins
*/

#include <stddef.h>
#include "mysh.h"
#include "builtins/builtins_func.h"
#include "str_func.h"
#include "macro_errors.h"

int exec_builtins(mysh_t *mysh, command_t to_exec)
{
    for (int i = 0; all_builtins[i].function != NULL; i += 1) {
        if (my_strcmp(to_exec.command[0], all_builtins[i].command) == 0) {
            return all_builtins[i].function(mysh, to_exec);
        }
    }
    return FAILURE;
}
