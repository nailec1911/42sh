/*
** EPITECH PROJECT, 2023
** exec_command
** File description:
** exec_job
*/

#include <sys/wait.h>
#include "exec_command.h"
#include "job_control.h"
#include "macro_errors.h"
#include "parser/ast.h"

job_list *lookup_job(job_list *list, int *nb_job)
{
    int status;
    pid_t pid;
    and_command_t *job;

    if (!list || !nb_job)
        return NULL;
    while ((pid = waitpid(WAIT_ANY,
                    &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0) {
        update_process_status(list, pid, status);
        if (!(job = get_job_from_pid(list, pid)))
            return list;
        if (job_is_completed(job)) {
            display_job_status(get_job_from_id(list, job->job_id));
            list = remove_job_from_list(list, job->job_id);
            (*nb_job)--;
        }
    }
    return list;
}

static int exec_piped_process(mysh_t *mysh, and_command_t *job, int i)
{
    int res = 0;
    int tube[2];

    pipe(tube);
    job->tab_command[i].fd_in = tube[0];
    job->job_mode = PIPELINE;
    res = exec_process(mysh, job, &job->tab_command[i], true);
    close(tube[0]);
    job->tab_command[i - 1].fd_out = tube[1];

    return res;
}

int exec_job(mysh_t *mysh, and_command_t *job)
{
    int res = 0;
    mode init_mode = job->job_mode;

    if (!mysh || !job)
        return ERROR;
    lookup_job(mysh->list, &mysh->nb_current_job);
    for (int i = job->nb_command - 1; i >= 1; --i) {
        res = exec_piped_process(mysh, job, i);
    }
    job->job_mode = init_mode;
    res = exec_process(mysh, job,
        &job->tab_command[0], false);
    if (job->job_mode == BACKGROUND)
        display_background(job);
    else if (res == 0) {
        mysh->list = remove_job_from_list(mysh->list, job->job_id);
        mysh->nb_current_job--;
    }
    return res;
}
