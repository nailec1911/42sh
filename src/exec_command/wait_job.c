/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** wait_job
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

#include "exec_command.h"
#include "mysh.h"
#include "job_control.h"
#include "macro_errors.h"

bool job_is_stoped(job *j)
{
    for (process *p = j->head; p; p = p->next) {
        if (p->process_state != DONE && p->process_state != SUSPENDED)
            return false;
    }
    return true;
}

bool job_is_completed(job *j)
{
    for (process *p = j->head; p; p = p->next) {
        if (p->process_state != DONE)
            return false;
    }
    return true;
}

static int update_process_status(job *j, pid_t process_id, int status)
{
    if (process_id < 0)
        return -1;
    for (job *tmp = j; tmp; tmp = tmp->next) {
        for (process *p = tmp->head; p; p = p->next) {
            if (p->pid == process_id) {
                if (WSTOPSIG(status))
                    p->process_state = SUSPENDED;
                if (WIFEXITED(status)) {
                    p->process_state = DONE;
                }
                if (WIFSIGNALED(status))
                    p->process_state = TERMINATED;
            }
        }
    }
    return 0;
}

int wait_job(job *j)
{
    int status = 0;
    pid_t pid = 0;

    printf("wait job %d\n", j->pgid);
    do {
        pid = waitpid(j->pgid, &status, WUNTRACED);
        printf("waitpid = %d\n", pid);
    } while (!update_process_status(j, pid, status) &&
            !job_is_stoped(j) &&
            !job_is_completed(j));
    return SUCCESS;
}
