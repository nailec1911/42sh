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

#include "job_control.h"
#include "str_func.h"
#include "mysh.h"
#include "macro_errors.h"

static void set_foreground(mysh_t *mysh, and_command_t *job, int status)
{
    tcsetpgrp(mysh->shell_descriptor, job->pgid);
    if ((status = wait_job(mysh->list, job)) != SUCCESS)
        mysh->last_status = status;
    else {
        mysh->list = remove_job_from_list(mysh->list, job->job_id);
        mysh->nb_current_job--;
    }
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(mysh->shell_descriptor, getpid());
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

int do_fg(mysh_t *mysh, command_t to_exec)
{
    pid_t pid;

    if (verif_current_job(mysh) != SUCCESS)
        return SUCCESS;
    if (!to_exec.args[1]) {
        if (kill(mysh->list->job->pgid, SIGCONT) < 0) {
            fprintf(stderr, "fg: No such job.\n");
            return SUCCESS;
        }
        set_foreground(mysh, mysh->list->job, mysh->list->job->pgid);
    } else {
        if (((pid = atoi(to_exec.args[1])) <= 0) || (kill(pid, SIGCONT) < 0)) {
            fprintf(stderr, "fg: No such job\n");
            return SUCCESS;
        }
        set_foreground(mysh, get_job_from_pid(mysh->list, pid), pid);
    }
    return SUCCESS;
}
