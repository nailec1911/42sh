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
#include "parser/ast.h"

void display_job_status(and_command_t *job)
{
    if (job_is_completed(job)) {
        printf("[%d] Done\n", job->job_id);
        for (int i = 0; i < job->nb_command; ++i) {
            printf("%s", job->tab_command[i].args[0]);
            if (i + 1 < job->nb_command)
                printf(" | ");
        }
        printf("\n");
    }
}

int wait_job(job_list *list, and_command_t *job)
{
    int status;
    pid_t pid;
    short count = 0;

    do {
        pid = waitpid(WAIT_ANY, &status, WUNTRACED);
        update_process_status(list, pid, status);
        count++;
    } while (count < job->nb_command);

    return status;
}
