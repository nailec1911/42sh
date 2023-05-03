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

#include "job_control.h"
#include "launch_command.h"
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"
#include "mysh.h"
#include "init.h"

static char *choose_get_line(mysh_t mysh)
{
    char *input = "\0";
    mysh.ind_history = length_tab_hist(mysh.history.tab_hist);
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

    mysh->list = lookup_job(mysh->list, &mysh->nb_current_job);
    mysh->to_return = mysh->last_status;
    mysh->last_status = 0;
    if (input[0] == '\n')
        return SUCCESS;
    if ((res = handle_input(mysh, input)) == ERROR)
        return ERROR;
    if (res != SUCCESS)
        return SUCCESS;
    if ((res = loop_grocommand(mysh)) == ERROR)
        return ERROR;

    //free_ast(mysh->ast);
    return res;
}

static void set_main_process(mysh_t *mysh)
{
    mysh->tty = true;
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    mysh->shell_pgid = getpid();
    mysh->shell_descriptor = STDIN_FILENO;
    setpgid(mysh->shell_pgid, mysh->shell_pgid);
    tcsetpgrp(mysh->shell_descriptor, mysh->shell_pgid);
}

static int init_all(mysh_t *mysh, char * const env[])
{
    mysh->list = NULL;
    if (isatty(0) == 1)
        set_main_process(mysh);
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
        if (isatty(mysh.shell_descriptor))
            write(1, ":)  ", 3);
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
    free_env(&mysh);
    return mysh.to_return;
}
