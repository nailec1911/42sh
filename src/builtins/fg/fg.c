/*
** EPITECH PROJECT, 2023
** fg
** File description:
** fg
*/

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#include "job_control.h"
#include "str_func.h"
#include "mysh.h"
#include "macro_errors.h"
#include "builtins/fg.h"

void set_foreground(mysh_t *mysh, and_command_t *job, pid_t pid)
{
    int status = 0;

    if (!mysh || !job)
        return;
    tcsetpgrp(SHELL_DESCRIPTOR, pid);
    if ((status = wait_job(mysh->list, job)) != SUCCESS)
        mysh->last_status = status;
    else {
        mysh->list = remove_job_from_list(mysh->list, job->job_id);
        mysh->nb_current_job--;
    }
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(SHELL_DESCRIPTOR, getpid());
}

static int verif_current_job(mysh_t *mysh)
{
    if (!mysh->list ||
            (strcmp(mysh->list->job->tab_command[0].args[0], "fg") == 0)) {
        fprintf(stderr, "No current job.\n");
        return FAILURE;
    }
    return SUCCESS;
}

int do_fg(mysh_t *mysh, command_t *to_exec)
{
    if (!mysh)
        return ERROR;
    if (verif_current_job(mysh) != SUCCESS)
        return SUCCESS;
    if (!to_exec->args[1])
        return fg_no_args(mysh);
    if (to_exec->args[1][0] == '%' && strlen(to_exec->args[1]) > 1)
        return fg_with_jid(mysh, atoi(to_exec->args[1] + 1));
    return fg_with_pid(mysh, atoi(to_exec->args[1]));
}
