/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** env
*/

#include <stddef.h>
#include <unistd.h>
#include "str_func.h"
#include "mysh.h"
#include "macro_errors.h"

int do_env(mysh_t *mysh, command_t to_exec)
{
    env_var_t *temp = mysh->list_env;

    if (to_exec.command[1] != NULL) {
        my_putstr("env: ‘", 2);
        my_putstr(to_exec.command[1], 2);
        my_putstr("’: No such file or directory\n", 2);
        mysh->last_status = 127;
        return SUCCESS;
    }
    for (int i = 0; temp != NULL; i += 1){
        my_putstr(temp->var, to_exec.fd_out);
        write(to_exec.fd_out, "\n", 1);
        temp = temp->next;
    }
    mysh->last_status = 0;
    return SUCCESS;
}
