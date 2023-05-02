/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** update_process_status
*/

#include "job_control.h"
#include "macro_errors.h"
#include <stdlib.h>

static void set_process_status(command_t *process, int status)
{
    if (WIFEXITED(status))
        process->process_state = DONE;
    else if (WIFSTOPPED(status))
        process->process_state = SUSPENDED;
    else if (WIFCONTINUED(status))
        process->process_state = CONTINUED;
}

static bool iterate_process(and_command_t *job, pid_t pid, int status)
{
    for (int i = 0; i < job->nb_command; ++i) {
        if (job->tab_command[i].pid == pid) {
            set_process_status(&job->tab_command[i], status);
            return true;
        }
    }
    return false;
}

int update_process_status(job_list *list, pid_t pid, int status)
{
    if (pid < 0)
        return SUCCESS;

    for (job_list *tmp = list; tmp; tmp = tmp->next) {
        if (iterate_process(tmp->job, pid, status)) {
            return SUCCESS;
        }
    }
    return SUCCESS;
}
