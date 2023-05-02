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

static void display_error_exec(int error_code, char *path)
{
    switch (error_code) {
        case (2):
            fprintf(stderr, "%s: Command not found\n", path);
            break;
        case (8):
            fprintf(stderr, "%s: Exec format error. Wrong Architecture.\n", path);
            break;
        case (20):
            fprintf(stderr, "%s: Not a directory.\n", path);
            break;
        case (13):
            fprintf(stderr, "%s: Permission denied.\n", path);
            break;
        default:
            perror(path);
    }
}

static int launch_child(command_t *process)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
    dup2(process->fd_out, STDOUT_FILENO);
    dup2(process->fd_in, STDIN_FILENO);
    if (execvp(process->args[0], process->args) == -1)
        display_error_exec(errno, process->args[0]);
    exit(0);
}


static int exec_process(mysh_t *mysh, and_command_t *job, command_t *process)
{
    pid_t pid;
    int status = 0;
    if ((status = exec_builtins(mysh, *process)) != FAILURE)
        return status;

    if ((pid = fork()) < 0)
        return FAILURE;
    if (pid == 0) {
        launch_child(process);
    } else {
        process->pid = pid;
        if (job->pgid == 0)
            job->pgid = process->pid;
        setpgid(process->pid, job->pgid);
        if (job->job_mode == FOREGROUND) {
            tcsetpgrp(mysh->shell_descriptor, job->pgid);
            status = wait_job(mysh->list, job);
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(mysh->shell_descriptor, getpid());
            signal(SIGTTOU, SIG_DFL);
        }
    }
    return status;
}

void display_background(and_command_t *job)
{
    printf("[%d]", job->job_id);
    for (int i = 0; i < job->nb_command; ++i)
        printf(" %d", job->tab_command[i].pid);
    printf("\n");
}

void loopkup_job(job_list *list, int *nb_job)
{
    int status;
    pid_t pid;
    int jid = -1;

    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0) {
        update_process_status(list, pid, status);
        if ((jid = get_job_id(list, pid)) != -1 && job_is_completed(get_job_from_id(list, jid))) {
            display_job_status(get_job_from_id(list, jid));
            list = remove_job_from_list(list, jid);
            (*nb_job)--;
        }
    }
}

int exec_job(mysh_t *mysh, and_command_t *job)
{
    int tube[2];
    int res = 0;
    //job->job_mode = BACKGROUND;
    /*
    for (int i = job->nb_command - 1; i >= 0; --i) {
        if (i - 1 >= 0) {
            pipe(tube);
            job->tab_command[i].fd_in = tube[0];
            res = exec_process(mysh, job, &job->tab_command[i]);
            close(tube[0]);
            job->tab_command[i - 1].fd_out = tube[1];
        } else
            res = exec_process(mysh, job, &job->tab_command[i]);
    }
    */
    loopkup_job(mysh->list, &mysh->nb_current_job);
    for (int i = 0; i < job->nb_command; ++i) {
        if (!job->tab_command[i].is_last) {
            pipe(tube);
            job->tab_command[i].fd_out = tube[1];
            res = exec_process(mysh, job, &job->tab_command[i]);
            close(tube[1]);
            job->tab_command[i + 1].fd_in = tube[0];
        } else
            res = exec_process(mysh, job, &job->tab_command[i]);
    }
    if (job->job_mode == BACKGROUND)
        display_background(job);
    else {
        mysh->list = remove_job_from_list(mysh->list, job->job_id);
        mysh->nb_current_job--;
    }
    return res;
}
