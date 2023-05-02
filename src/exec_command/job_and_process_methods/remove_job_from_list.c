/*
** EPITECH PROJECT, 2023
** exec_command
** File description:
** remove_job_from_list
*/

#include <stdlib.h>
#include "job_control.h"

job_list *remove_job_from_list(job_list *list, int job_id)
{
    int position = 0;
    job_list *tmp = list;

    if (job_id < 0)
        return list;
    position = job_id - 1;
    if (position == 0) {
        list = list->next;
        return list;
    } else {
        for (int i = 0; i < position - 1 && tmp; ++i)
            tmp = tmp->next;
        tmp = tmp->next->next;
    }
    return list;
}
