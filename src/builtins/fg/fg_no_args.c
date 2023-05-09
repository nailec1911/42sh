/*
** EPITECH PROJECT, 2023
** fg
** File description:
** fg_no_args
*/

#include "mysh.h"
#include "string.h"
#include "builtins/fg.h"
#include "job_control.h"
#include "macro_errors.h"


static pid_t get_last_job_pgid(job_list *list)
{
    job_list *job = list;

    if (!job)
        return -1;
    for (; job->next && strcmp(job->next->job->tab_command[0].args[0], "fg")
            != SUCCESS; job = job->next);
    return job->job->pgid;
}

int fg_no_args(mysh_t *mysh)
{
    pid_t pid = 0;

    if (!mysh)
        return ERROR;
    pid = get_last_job_pgid(mysh->list);
    if (pid <= 0)
        return ERROR;
    if (send_cont(pid) != SUCCESS) {
        mysh->last_status = FAILURE;
        return SUCCESS;
    }
    set_foreground(mysh, get_job_from_pid(mysh->list, pid), pid);
    return SUCCESS;
}
