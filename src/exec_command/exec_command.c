/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** exec_command
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"
#include "exec_command.h"

static void display_error_exec(int error_code, char *path)
{
    if (error_code == 8) {
        my_putstr(path, 2);
        my_putstr(": Exec format error. Wrong Architecture.\n", 2);
        return;
    }
    if (error_code == 20) {
        my_putstr(path, 2);
        my_putstr(": Not a directory.\n", 2);
        return;
    }
    if (error_code == 13) {
        my_putstr(path, 2);
        my_putstr(": Permission denied.\n", 2);
        return;
    }
    perror(path);
}

static void parent_fork(all_args_t *all_args, int cpid, command_t command)
{
    int status = 0;

    if (command.fd_out != STDOUT_FILENO)
        close(command.fd_out);
    if (command.is_last)
        waitpid(cpid, &status, WUNTRACED);
    else
        waitpid(cpid, &status, WNOHANG);
    status = handle_errors(status);
    if (status != 0)
        all_args->last_status = status;
}

static int get_res_command(all_args_t *all_args,
char * const env[], char *to_exec, command_t command)
{
    pid_t  cpid;

    if ((cpid = fork()) == -1)
        return ERROR;
    if (cpid == 0) {
        dup2(command.fd_out, STDOUT_FILENO);
        dup2(command.fd_in, STDIN_FILENO);
        execve(to_exec, all_args->command, env);
        display_error_exec(errno, all_args->command[0]);
        exit(errno);
    }
    parent_fork(all_args, cpid, command);
    return SUCCESS;
}

int exec_binary(all_args_t *all_args, char *path_to_exec, command_t to_exec)
{
    char **env = set_new_env(all_args->list_env);

    if (env == NULL)
        return ERROR;

    if ((get_res_command(all_args, env, path_to_exec, to_exec)) == ERROR)
        return ERROR;

    free(env);
    return SUCCESS;
}

int exec_command(all_args_t *all_args, command_t to_exec)
{
    int res = 0;
    char *path_to_exec = NULL;

    all_args->command = to_exec.command;
    if ((res = exec_builtins(all_args, to_exec)) != FAILURE)
        return res;

    if ((res = get_path(all_args, &path_to_exec)) == ERROR)
        return ERROR;
    if (res != SUCCESS){
        my_putstr(all_args->command[0], 2);
        write(2, ": Command not found.\n", 21);
        all_args->last_status = 1;
        return SUCCESS;
    }
    if (exec_binary(all_args, path_to_exec, to_exec) == ERROR)
        return ERROR;
    free(path_to_exec);
    return SUCCESS;
}
