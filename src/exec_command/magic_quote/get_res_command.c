/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_res_command
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <string.h>
#include "macro_errors.h"
#include "magic_quote.h"
#include "str_func.h"

static void redirect_exec(mysh_t *mysh, char *quoted, int fd_entry)
{
    dup2(fd_entry, STDOUT_FILENO);
    loop_sh(mysh, quoted);
    exit(0);
}

FILE *get_file_res_command(mysh_t *mysh, char *quoted)
{
    int pipefd[2] = {0};
    pid_t pid;
    FILE *res;

    quoted[strlen(quoted) - 1] = '\n';
    if (pipe(pipefd) == -1 || (pid = fork()) == -1)
        return NULL;
    if (pid == 0)
        redirect_exec(mysh, quoted, pipefd[1]);
    waitpid(pid, NULL, WUNTRACED);
    close(pipefd[1]);
    res = fdopen(pipefd[0], "r");
    return res;
}
