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
#include <signal.h>
#include "builtins/vars.h"
#include "mysh.h"
#include "launch_command.h"
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"
#include "init.h"

static char *choose_get_line(mysh_t mysh)
{
    char *input = "\0";
    mysh.ind_history = mysh.history.len_tab_hist;
    mysh.ind_init = mysh.ind_history;

    if (mysh.tty)
        input = get_input(mysh);
    else
        input = get_input_line();
    return input;
}

int loop_sh(mysh_t *mysh, char *input)
{
    int res = 0;

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
    free_ast(mysh->ast);
    return res;
}

static int init_all(mysh_t *mysh, char * const env[])
{
    mysh->vars = 0;
    if (isatty(0) == 1)
        mysh->tty = true;
    if ((mysh->env = init_mysh_env(env)) == NULL)
        return ERROR;
    if (init_history(&mysh->history) == ERROR)
        return ERROR;
    if (init_alias(&mysh->alias) == ERROR)
        return ERROR;
    return SUCCESS;
}

static int destroy_all(mysh_t *mysh)
{
    free_env(mysh);
    vars_t *vars = mysh->vars;
    while (vars) {
        vars_t *tmp = vars->next;
        free_global_var(vars);
        vars = tmp;
    }
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
        if (mysh.tty)
            write(1, "xD ", 3);
        if ((input = choose_get_line(mysh)) == NULL) {
            res = EXIT;
            break;
        }
        res = loop_sh(&mysh, input);
    }
    if (res == EXIT && mysh.tty)
        fprintf(stdout, "exit\n");
    if (res == ERROR)
        return ERROR;
    destroy_all(&mysh);
    return mysh.to_return;
}
