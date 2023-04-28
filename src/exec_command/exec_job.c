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

#include "exec_command.h"
#include "mysh.h"
#include "job_control.h"
#include "macro_errors.h"

static void display_error_exec(int error_code, char *path)
{
    if (error_code == 8) {
        fprintf(stderr, "%s: Exec format error. Wrong Architecture.\n", path);
        return;
    }
    if (error_code == 20) {
        fprintf(stderr, "%s: Not a directory.\n", path);
        return;
    }
    if (error_code == 13) {
        fprintf(stderr, "%s: Permission denied.\n", path);
        return;
    }
    perror(path);
}
static int launch_child(process *p)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
    dup2(p->fd_out, STDOUT_FILENO);
    dup2(p->fd_in, STDIN_FILENO);
    execvp(p->args[0], p->args);
    display_error_exec(errno, p->args[0]);
    exit(0);
}

static int exec_process(job *j, process *p)
{
    pid_t pid;
    int status = 0;

    if ((pid = fork()) < 0)
        return FAILURE;
    if (pid == 0) {
        launch_child(p);
    } else {
        p->pid = pid;
        if (j->pgid == 0)
            j->pgid = p->pid;
        setpgid(p->pid, j->pgid);
        printf("exec : %d\n", p->pid);
        if (j->job_mode == FOREGROUND) {
            tcsetpgrp(0, j->pgid);
            status = wait_job(j);
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(0, getpid());
            signal(SIGTTOU, SIG_DFL);
        }
    }
    return status;
}

int exec_job(job *j)
{
    int tube[2];
    for (process *p = j->head; p; p = p->next) {
        if (p->next) {
            pipe(tube);
            p->fd_out = tube[1];
            exec_process(j, p);
            close(tube[1]);
            p->next->fd_in = tube[0];
        } else {
            exec_process(j, p);
        }
    }
    return SUCCESS;
}
