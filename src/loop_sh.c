/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** loop_sh
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "builtins/vars.h"
#include "mysh.h"
#include "job_control.h"
#include "launch_command.h"
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"
#include "init.h"

int loop_sh(mysh_t *mysh, char *input)
{
    int res = 0;

    mysh->list = lookup_job(mysh->list, &mysh->nb_current_job);
    mysh->to_return = mysh->last_status;
    mysh->last_status = 0;
    if (input[0] == '\n')
        return SUCCESS;
    if ((res = handle_input(mysh, input)) == ERROR)
        return ERROR;
    if (res != SUCCESS)
        return SUCCESS;
    if ((res = loop_grocommand(mysh, &(mysh->ast))) == ERROR)
        return ERROR;
    return res;
}
