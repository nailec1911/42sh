/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** exec_pipes
*/

#include "exec_command.h"
#include "macro_errors.h"
#include "globbins.h"

int exec_and_command(mysh_t *mysh, and_command_t *to_exec)
{
    int res = 0;
    (void)mysh;
    update_glob_argv(to_exec);

    if ((res = set_fd_input(&(to_exec->tab_command[0]))) == EXIT)
        return SUCCESS;
    if (res == ERROR)
        return ERROR;
    if (set_fd_output(&(to_exec->tab_command[to_exec->nb_command - 1]))
            == ERROR)
        return ERROR;

    return SUCCESS;
}
