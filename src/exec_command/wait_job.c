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

int wait_job(job_list *list, and_command_t *job)
{
    int status;
    int res = 0;
    pid_t pid;
    short count = 0;

    if (!list || !job)
        return 0;
    do {
        pid = waitpid(-job->pgid, &status, WUNTRACED);
        res = handle_errors(status);
        update_process_status(list, pid, status);
        count++;
    } while (count < 1);

    status = (res != 0) ? res : status;

    return status;
}
