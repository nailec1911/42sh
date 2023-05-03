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

/*

static char **copy_args(char **args_to_copy, int nb_args)
{
    char **result = malloc(sizeof(char*) * (nb_args + 1));
    int args_len = 0;

    if (!result)
        return NULL;
    result[nb_args] = NULL;
    for (int i = 0; args_to_copy[i]; ++i) {
        args_len = strlen(args_to_copy[i]);
        result[i] = malloc(sizeof(char) * (args_len + 1));
        result[i][args_len] = '\0';
        for (int j = 0; args_to_copy[i][j]; ++j)
            result[i][j] = args_to_copy[i][j];
    }
    return result;
}

static command_t *copy_cmd_tab(and_command_t *job)
{
    command_t *tab = malloc(sizeof(command_t) * job->nb_command);

    if (!tab)
        return NULL;
    for (int i = 0; i < job->nb_command; ++i) {
        tab[i].nb_command = job->tab_command[i].nb_command;
        tab[i].pid = job->tab_command[i].pid;
        if ((tab[i].args = copy_args(job->tab_command[i].args, job->nb_command)) == NULL)
            return NULL;
        tab[i].path = job->tab_command[i].path;
        tab[i].fd_in = job->tab_command[i].fd_in;
        tab[i].fd_out = job->tab_command[i].fd_out;
        tab[i].is_last = job->tab_command[i].is_last;
        tab[i].redirect_in = job->tab_command[i].redirect_in;
        tab[i].redirect_out = job->tab_command[i].redirect_out;
        tab[i].process_state = job->tab_command[i].process_state;
    }
    return tab;
}

*/

static job_list *init_list(and_command_t *job)
{
    job_list *list = malloc(sizeof(job_list));
    list->job = job;
    list->next = NULL;
    /*
    list->job->pgid = job->pgid;
    list->job->job_id = job->job_id;
    list->job->job_mode = job->job_mode;
    list->job->nb_command = job->nb_command;
    list->job->tab_command = copy_cmd_tab(job);
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
