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
#include "mysh.h"
#include "init.h"

static char *choose_get_line(void)
{
    char *input = '\0';

    if (isatty(0) == 1)
        input = get_input();
    else
        input = get_input_line();
    return input;
}

int loop_sh(mysh_t *mysh, char *input)
{
    int res = 0;

    if (input[0] == '\n')
        return SUCCESS;
    if ((res = handle_input(mysh, input)) == ERROR)
        return ERROR;
    if (res != SUCCESS)
        return SUCCESS;
    if ((res = loop_grocommand(mysh)) == ERROR)
        return ERROR;

    free_ast(mysh->ast);
    return res;
}

static int init_all(mysh_t *mysh, char * const env[])
{
    if ((mysh->env = init_mysh_env(env)) == NULL)
        return ERROR;
    if (init_history(mysh) == ERROR)
        return ERROR;
    if (init_alias(mysh) == ERROR)
        return ERROR;
    return SUCCESS;
}

int mysh(char * const env[])
{
    int res = 0;
    char *input = "\0";
    mysh_t mysh = {0};
    if (init_all(&mysh, env) == ERROR)
        return ERROR;
    while (res == 0) {
        if (isatty(0) == 1)
            write(1, "xD ", 3);
        if ((input = choose_get_line()) == NULL) {
            res = EXIT;
            break;
        }
        res = loop_sh(&mysh, input);
    }
    if (res == EXIT && isatty(0) == 1)
        fprintf(stdout, "exit\n");
    if (res == ERROR)
        return ERROR;
    free_env(&mysh);
    return mysh.to_return;
}
