/*
** EPITECH PROJECT, 2023
** fg
** File description:
** send_cont
*/

#include <job_control.h>
#include <sys/wait.h>
#include <signal.h>

#include "macro_errors.h"

int send_cont(pid_t pid)
{
    if (kill(pid, SIGCONT) < 0) {
        fprintf(stderr, "fg: No such job\n");
        return FAILURE;
    }
    return SUCCESS;
}
