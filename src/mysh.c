/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** mysh
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "launch_command.h"
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"

static char *choose_get_line(void)
{
    char *input = '\0';

    if (isatty(0) == 1)
        input = get_input();
    else
        input = get_input_line();
    return input;
}

static int loop_sh(all_args_t *all_args, char *input)
{
    int res = 0;

    if (input[0] == '\n')
        return SUCCESS;
    if ((res = parse_input(input, all_args)) == ERROR)
        return ERROR;
    if (res != SUCCESS)
        return SUCCESS;

    if ((res = go_throught_grocommand(all_args)) == ERROR)
        return ERROR;

    free_ast(all_args->ast);
    return res;
}

int mysh(char * const env[])
{
    int res = 0;
    char *input = "\0";
    all_args_t all_args = {0};
    if ((all_args.list_env = create_list_env(env)) == NULL && env[0] != NULL)
        return ERROR;
    while (res == 0) {
        if (isatty(0) == 1)
            write(1, "$> ", 3);
        if ((input = choose_get_line()) == NULL) {
            res = EXIT;
            break;
        }
        res = loop_sh(&all_args, input);
    }
    if (res == EXIT && isatty(0) == 1)
        write(1, "exit\n", 5);
    if (res == ERROR)
        return ERROR;
    free_env(&all_args);
    return all_args.to_return;
}
