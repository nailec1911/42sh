/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** add_job_to_list
*/

#include <string.h>
#include "job_control.h"
#include "parser/ast.h"
#include "str_func.h"

static job_list *init_list(and_command_t *job)
{
    job_list *list = malloc(sizeof(job_list));

    if (!list || !job)
        return NULL;
    list->job = job;
    list->next = NULL;
    return list;
}

job_list *add_job_to_list(job_list *list, and_command_t *job)
{
    job_list *tmp = list;

    if (!list || !job)
        return init_list(job);
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = init_list(job);
    tmp->next->next = NULL;

    return list;
}
