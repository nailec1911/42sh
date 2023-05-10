/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_job_from_pid
*/

#include <stdio.h>
#include <stdlib.h>
#include "job_control.h"
#include "parser/ast.h"

static int get_job_loop(and_command_t *job, pid_t pid)
{
    if (!job)
        return -1;
    for (int i = 0; i < job->nb_command; ++i) {
        if (job->tab_command[i].pid == pid)
            return job->job_id;
    }
    return -1;
}

and_command_t *get_job_from_pid(job_list *list, pid_t pid)
{
    int id = -1;

    if (!list)
        return NULL;
    for (job_list *tmp = list; tmp; tmp = tmp->next) {
        if ((id = get_job_loop(tmp->job, pid)) != -1)
            return tmp->job;
    }

    return NULL;
}
