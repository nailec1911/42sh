/*
** EPITECH PROJECT, 2023
** merge_jib
** File description:
** exec_process
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

#include "mysh.h"
#include "exec_command.h"
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
    if (process->fd_out != STDOUT_FILENO)
        dup2(process->fd_out, STDOUT_FILENO);
    if (process->fd_in != STDIN_FILENO)
        dup2(process->fd_in, STDIN_FILENO);
    if (execve(process->path, process->args, mysh->env) == -1) {
        display_error_exec(errno, process->args[0]);
        if (errno == 2)
            exit(1);
        exit(errno);
    }
}

static int
set_foreground_execution(mysh_t *mysh, and_command_t *job, int status)
{
    tcsetpgrp(SHELL_DESCRIPTOR, job->pgid);
    if ((status = wait_job(mysh->list, job)) != SUCCESS)
        mysh->last_status = status;
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(SHELL_DESCRIPTOR, getpid());
    return status;
}

static int exec_fork(mysh_t *mysh, and_command_t *job, command_t *process)
{
    pid_t pid;
    int status = 0;

    if ((pid = fork()) < 0)
        return FAILURE;
    if (pid == 0) {
        if ((status = exec_builtins(mysh, process)) != FAILURE)
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

int
exec_process(mysh_t *mysh, and_command_t *job, command_t *process, bool do_fork)
{
    int status = 0;

    if (process->is_ast)
        return exec_parenthesis(mysh, process);
    if (!do_fork && (status = exec_builtins(mysh, process)) != FAILURE)
        return status;
    if (get_path(mysh, &process->path, process) == ERROR)
        return ERROR;

    return exec_fork(mysh, job, process);
}
