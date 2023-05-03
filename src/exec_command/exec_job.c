/*
** EPITECH PROJECT, 2023
** exec_command
** File description:
** exec_job
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

static void launch_child(mysh_t *mysh, command_t *process)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
    dup2(process->fd_out, STDOUT_FILENO);
    dup2(process->fd_in, STDIN_FILENO);
    if (execve(process->path, process->args, mysh->env) == -1) {
        display_error_exec(errno, process->args[0]);
        exit(1);
    }
}

static int
set_foreground_execution(mysh_t *mysh, and_command_t *job, int status)
{
    tcsetpgrp(mysh->shell_descriptor, job->pgid);
    if ((status = wait_job(mysh->list, job)) != SUCCESS)
        mysh->last_status = status;
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(mysh->shell_descriptor, getpid());
    signal(SIGTTOU, SIG_DFL);
    return status;
}

static int
exec_process(mysh_t *mysh, and_command_t *job, command_t *process, bool pipe)
{
    pid_t pid;
    int status = 0;
    get_path(mysh, &process->path, *process);
    if (!pipe && (status = exec_builtins(mysh, *process)) != FAILURE)
        return status;
    if ((pid = fork()) < 0)
        return FAILURE;
    if (pid == 0) {
        if (pipe && (status = exec_builtins(mysh, *process)) != FAILURE)
            exit(status);
        launch_child(mysh, process);
    } else {
        process->pid = pid;
        if (job->pgid == 0)
            job->pgid = process->pid;
        setpgid(process->pid, job->pgid);
        if (job->job_mode == FOREGROUND)
            status = set_foreground_execution(mysh, job, status);
    }
    return status;
}

job_list *lookup_job(job_list *list, int *nb_job)
{
    int status;
    pid_t pid;
    and_command_t *job;

    while ((pid = waitpid(WAIT_ANY,
                    &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0) {
        update_process_status(list, pid, status);
        job = get_job_from_pid(list, pid);
        if (job_is_completed(job)) {
            display_job_status(get_job_from_id(list, job->job_id));
            list = remove_job_from_list(list, job->job_id);
            (*nb_job)--;
        }
    }
    return list;
}

int exec_job(mysh_t *mysh, and_command_t *job)
{
    int tube[2];
    int res = 0;
    lookup_job(mysh->list, &mysh->nb_current_job);
    //job->job_mode = BACKGROUND;
    for (int i = 0; i < job->nb_command - 1; ++i) {
        pipe(tube);
        job->tab_command[i].fd_out = tube[1];
        res = exec_process(mysh, job, &job->tab_command[i], true);
        close(tube[1]);
        job->tab_command[i + 1].fd_in = tube[0];
    }
    res = exec_process(mysh, job,
        &job->tab_command[job->nb_command - 1], false);
    if (job->job_mode == BACKGROUND)
        display_background(job);
    else {
        mysh->list = remove_job_from_list(mysh->list, job->job_id);
        mysh->nb_current_job--;
    }
    return res;
}
