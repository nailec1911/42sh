/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_job_status
*/

#include "job_control.h"

bool job_is_stoped(and_command_t *job)
{
    for (int i = 0; i < job->nb_command; ++i) {
        if (job->tab_command[i].process_state != DONE ||
                job->tab_command[i].process_state != SUSPENDED)
            return false;
    }
    return true;
}

bool job_is_completed(and_command_t *job)
{
    for (int i = 0; i < job->nb_command; ++i) {
        if (job->tab_command[i].process_state != DONE)
            return false;
    }
    return true;
}
