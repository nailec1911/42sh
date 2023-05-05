/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** zz
*/

#include <stdlib.h>

#include "builtins/repeat.h"
#include "exec_command.h"
#include "mysh.h"
#include "macro_errors.h"

int do_repeat(mysh_t *mysh, command_t to_exec)
{
    int status = 0;
    if (to_exec.nb_command < 3) {
        fprintf(stderr, "repeat: Too few arguments.\n");
        return SUCCESS;
    }

    command_t tmp = to_exec;
    tmp.command = &to_exec.command[2];
    tmp.nb_command = to_exec.nb_command - 2;

    for (int i = 0; i < atoi(to_exec.command[1]); i++) {
        status = exec_command(mysh, tmp);
        if (status == 84)
            return (status);
    }
    return (status);
}
