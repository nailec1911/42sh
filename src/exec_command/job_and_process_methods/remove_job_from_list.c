/*
** EPITECH PROJECT, 2023
** exec_command
** File description:
** remove_job_from_list
*/

#include <stdlib.h>
#include "job_control.h"

static int get_job_pos(job_list *list, int job_id)
{
    int pos = 0;
    if (!list)
        return -1;
    for (job_list *job = list; job; job = job->next) {
        if (job->job->job_id == job_id)
            return pos;
        pos++;
    }
    return -1;
}

job_list *remove_job_from_list(job_list *list, int job_id)
{
    int position = 0;
    job_list *tmp = list;

    if (job_id < 0 || !list)
        return list;
    if ((position = get_job_pos(list, job_id)) < 0)
        return list;
    if (position == 0) {
        list = list->next;
    } else {
        for (int i = 0; i < position - 1; ++i)
            tmp = tmp->next;
        job_list *del = tmp->next;
        tmp->next = tmp->next->next;
        del->next = NULL;
    }
    return list;
}
