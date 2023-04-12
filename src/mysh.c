/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** mysh
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "launch_command.h"
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"

static int loop_sh(mysh_t *mysh, char *input)
{
    int res = 0;

    if (input[0] == '\n')
        return SUCCESS;
    if ((res = parse_input(input, mysh)) == ERROR)
        return ERROR;
    if (res != SUCCESS)
        return SUCCESS;

    if ((res = go_throught_grocommand(mysh)) == ERROR)
        return ERROR;

    free_ast(mysh->ast);
    return res;
}

int mysh(char * const env[])
{
    int res = 0;
    char *input = "\0";
    mysh_t mysh = {0};
    if ((mysh.list_env = create_list_env(env)) == NULL && env[0] != NULL)
        return ERROR;
    while (res == 0) {
        if (isatty(0) == 1)
            write(1, "$> ", 3);
        if ((input = get_input()) == NULL) {
            res = EXIT;
            break;
        }
        res = loop_sh(&mysh, input);
    }
    if (res == EXIT && isatty(0) == 1)
        write(1, "exit\n", 5);
    if (res == ERROR)
        return ERROR;
    free_env(&mysh);
    return mysh.to_return;
}
