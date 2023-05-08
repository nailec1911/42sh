/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_last_job_pgid
*/

#include <string.h>
#include "job_control.h"
#include "macro_errors.h"

pid_t get_last_job_pgid(job_list *list)
{
    job_list *job = list;
    for (; job->next && strcmp(job->next->job->tab_command[0].args[0], "fg")
            != SUCCESS; job = job->next);
    return job->job->pgid;
}
