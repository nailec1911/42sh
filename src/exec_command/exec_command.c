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
int exec_parenthesis(mysh_t *mysh, command_t *to_exec);

static void parent_fork(mysh_t *mysh, int cpid, command_t command)
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
        mysh->last_status = status;
}

static int exec_binary(mysh_t *mysh, command_t command)
{
    pid_t  cpid;

    if ((cpid = fork()) == -1)
        return ERROR;
    if (cpid == 0) {
        dup2(command.fd_out, STDOUT_FILENO);
        dup2(command.fd_in, STDIN_FILENO);
        execvp(command.args[0], command.args);
        display_error_exec(errno, command.args[0]);
        exit(errno);
    }
    parent_fork(mysh, cpid, command);
    return SUCCESS;
}

int exec_command(mysh_t *mysh, command_t to_exec)
{
    int res = 0;

    to_exec.path = NULL;
    mysh->command = to_exec.args;
    if ((res = exec_builtins(mysh, to_exec)) != FAILURE)
        return res;
    if ((res = get_path(mysh, &(to_exec.args[0]), to_exec)) == ERROR)
        return ERROR;
    if (res != SUCCESS) {
        fprintf(stderr, "%s: Command not found.\n", to_exec.args[0]);
        mysh->last_status = 1;
        return SUCCESS;
    }
    if (exec_binary(mysh, to_exec) == ERROR)
        return ERROR;
    return SUCCESS;
}
