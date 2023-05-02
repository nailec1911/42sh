/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** add_job_to_list
*/

#include "job_control.h"

static job_list *init_list(and_command_t *job)
{
    job_list *list = malloc(sizeof(job_list));

    if (!list)
        return NULL;
    list->job = job;
    list->next = NULL;
    /*
    list->job->pgid = job->pgid;
    list->job->job_id = job->job_id;
    list->job->job_mode = job->job_mode;
    list->job->nb_command = job->nb_command;
    list->job->tab_command = malloc(sizeof(and_command_t));
    */
    return list;
}

job_list *add_job_to_list(job_list *list, and_command_t *job)
{
    job_list *tmp = list;

    if (!list)
        return init_list(job);
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = init_list(job);
    tmp->next->next = NULL;

    return list;
}
