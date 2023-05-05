/*
** EPITECH PROJECT, 2023
** fg
** File description:
** fg
*/

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include "job_control.h"
#include "str_func.h"
#include "mysh.h"
#include "macro_errors.h"

int do_fg(mysh_t *mysh, command_t to_exec)
{
    pid_t pid;
    int position = 0;
    job_list *tmp = mysh->list;
    if (to_exec.args[1] == NULL) {
        fprintf(stderr, "Usage : fd <pid>\n");
        return SUCCESS;
    }
    pid = atoi(to_exec.args[1]);
    position = get_job_id(mysh->list, pid);
    for (int i = 0; i < position; ++i)
        tmp = tmp->next;
    return SUCCESS;
}
