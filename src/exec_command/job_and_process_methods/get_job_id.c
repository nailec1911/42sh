/*
** EPITECH PROJECT, 2023
** exec_command
** File description:
** get_job_id
*/

#include "job_control.h"

static int get_job_id_loop(and_command_t *job, pid_t pid)
{
    for (int i = 0; i < job->nb_command; ++i) {
        if (job->tab_command[i].pid == pid)
            return job->job_id;
    }
    return -1;
}

int get_job_id(job_list *list, pid_t pid)
{
    int id = -1;

    for (job_list *tmp = list; tmp; tmp = tmp->next) {
        if ((id = get_job_id_loop(tmp->job, pid)) != -1)
            return id;
    }

    return -1;
}
