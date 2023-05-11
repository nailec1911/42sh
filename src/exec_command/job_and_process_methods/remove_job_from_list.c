/*
** EPITECH PROJECT, 2023
** exec_command
** File description:
** remove_job_from_list
*/

#include <stdlib.h>
#include <fcntl.h>
#include "job_control.h"
#include "parser/ast.h"

static void free_command(command_t *process)
{
    if (process->is_ast) {
        free_ast(process->parenthesis);
        return;
    }
    for (int i = 0; process->args[i]; ++i)
        free(process->args[i]);
    free(process->args);
    free(process->path);
}

static void free_and_command(and_command_t *job)
{
    for (int i = 0; i < job->nb_command; ++i) {
        free_command(&job->tab_command[i]);
    }

    free(job->tab_command);
}

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
        free_and_command(tmp->job);
        free(tmp);
    } else {
        for (int i = 0; i < position - 1; ++i)
            tmp = tmp->next;
        job_list *del = tmp->next;
        tmp->next = tmp->next->next;
        del->next = NULL;
        free_and_command(del->job);
        free(del);
    }
    return list;
}
