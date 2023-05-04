/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** handle_errors
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "macro_errors.h"
#include "str_func.h"

int handle_errors(int status)
{
    if (WIFSIGNALED(status)){
        if (WTERMSIG(status) == SIGFPE)
            fprintf(stderr, "Floating exception");
        else
            fprintf(stderr, "%s", strsignal(WTERMSIG(status)));
        if (WCOREDUMP(status))
            fprintf(stderr, " (core dumped)");
        fprintf(stderr, "\n");
        return status;
    }
    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == 13)
            return 1;
        if (WEXITSTATUS(status) == 8)
            return 126;
        return WEXITSTATUS(status);
    }
    if (WIFSTOPPED(status))
        return WSTOPSIG(status);
    return SUCCESS;
}
