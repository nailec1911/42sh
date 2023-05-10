/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** display_job
*/

#include <stdio.h>
#include "job_control.h"

void display_job_status(and_command_t *job)
{
    if (!job)
        return;
    printf("[%d] Done", job->job_id);
    for (int i = 0; i < job->nb_command; ++i) {
        printf(" %s", job->tab_command[i].args[0]);
        if (i + 1 < job->nb_command)
            printf(" |");
    }
    printf("\n");
}

void display_background(and_command_t *job)
{
    if (!job)
        return;
    printf("[%d]", job->job_id);
    for (int i = 0; i < job->nb_command; ++i)
        printf(" %d", job->tab_command[i].pid);
    printf("\n");
}
