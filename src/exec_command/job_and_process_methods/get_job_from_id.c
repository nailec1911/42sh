/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_job_from_id
*/

#include "job_control.h"

and_command_t *get_job_from_id(job_list *list, int job_id)
{
    if (job_id < 0 || !list)
        return NULL;

    for (job_list *tmp = list; tmp; tmp = tmp->next) {
        if (tmp->job->job_id == job_id)
            return tmp->job;
    }
    return NULL;
}
