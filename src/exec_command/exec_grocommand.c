/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** exec_grocommand
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "exec_command.h"
#include "macro_errors.h"

static void close_all_fd_except(grocommand_t to_exec, int except)
{
    for (int i = 0; i < to_exec.nb_command; i += 1) {
        if (i == except)
            continue;
        if (to_exec.tab_command[i].fd_out != STDOUT_FILENO)
            close(to_exec.tab_command[i].fd_out);
        if (to_exec.tab_command[i].fd_in != STDIN_FILENO)
            close(to_exec.tab_command[i].fd_in);
    }
}

static int fork_before_exec(all_args_t *all_args, grocommand_t to_exec, int i)
{
    int cpid = 0;

    if ((cpid = fork()) == -1)
        return ERROR;
    if (cpid == 0) {
        close_all_fd_except(to_exec, i);
        if (exec_command(all_args, to_exec.tab_command[i]) == ERROR) {
            exit(0);
        }
        exit(all_args->last_status);
    }
    return SUCCESS;
}

static int exec_all_function(all_args_t *all_args, grocommand_t to_exec)
{
    int res = 0;

    for (int i = 0; i < to_exec.nb_command -1; i += 1) {
        if (fork_before_exec(all_args, to_exec, i) == ERROR)
            return ERROR;
    }
    close_all_fd_except(to_exec, to_exec.nb_command - 1);
    if ((res = exec_command(all_args,
    to_exec.tab_command[to_exec.nb_command - 1])) != SUCCESS)
        return res;
    return SUCCESS;
}

int exec_grocommand(all_args_t *all_args, grocommand_t to_exec)
{
    int res = 0;

    if ((res = set_fd_input(&(to_exec.tab_command[0]))) == EXIT)
        return SUCCESS;
    if (res == ERROR)
        return ERROR;
    if (set_fd_output(&(to_exec.tab_command[to_exec.nb_command - 1])) == ERROR)
        return ERROR;
    if ((res = exec_all_function(all_args, to_exec)) != SUCCESS)
        return res;

    return SUCCESS;
}
