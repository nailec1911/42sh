/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** mysh
*/

#include <signal.h>
#include "mysh.h"
#include "job_control.h"
#include "launch_command.h"
#include "builtins/env.h"
#include "macro_errors.h"
#include "init.h"

static char *choose_get_line(mysh_t mysh)
{
    char *input = "\0";
    mysh.ind_history = mysh.history.len_tab_hist;
    mysh.ind_init = mysh.ind_history;

    if (isatty(SHELL_DESCRIPTOR))
        input = get_input(mysh);
    else
        input = get_input_line();
    return input;
}

static void set_main_process(mysh_t *mysh)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    mysh->shell_pgid = getpid();
    setpgid(mysh->shell_pgid, mysh->shell_pgid);
    tcsetpgrp(SHELL_DESCRIPTOR, mysh->shell_pgid);
}

static int init_all(mysh_t *mysh, char * const env[])
{
    mysh->vars = 0;
    mysh->list = NULL;
    mysh->completion.display = false;
    mysh->completion.index = -1;
    mysh->enter = false;
    mysh->completion.nb_lines = 0;
    set_main_process(mysh);
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
        init_prompt(&mysh);
        if ((input = choose_get_line(mysh)) == NULL) {
            res = EXIT;
            break;
        }
        res = loop_sh(&mysh, input);
    }
    if (res == EXIT && isatty(SHELL_DESCRIPTOR))
        fprintf(stdout, "exit\n");
    if (res == ERROR)
        return ERROR;
    destroy_all(&mysh);
    return mysh.to_return;
}
