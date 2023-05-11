/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exec_parenthesis
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "macro_errors.h"
#include "mysh.h"
#include "str_func.h"
#include "exec_command.h"

static int exec_ast(mysh_t *mysh, command_t *to_exec)
{
    dup2(to_exec->fd_out, STDOUT_FILENO);
    dup2(to_exec->fd_in, STDIN_FILENO);

    loop_grocommand(mysh, to_exec->parenthesis);
    exit(mysh->last_status);
}

int exec_parenthesis(mysh_t *mysh, command_t *to_exec)
{
    pid_t pid;
    int status = 0;

    if (!mysh || !to_exec)
        return ERROR;
    if ((pid = fork()) == -1)
        return ERROR;
    if (pid == 0)
        exec_ast(mysh, to_exec);
    waitpid(pid, &status, WUNTRACED);
    if (WIFEXITED(status))
        mysh->last_status = WEXITSTATUS(status);
    if (to_exec->fd_in != STDIN_FILENO)
        close(to_exec->fd_in);
    if (to_exec->fd_out != STDOUT_FILENO)
        close(to_exec->fd_out);
    return SUCCESS;
}
