/*
** EPITECH PROJECT, 2023
** fg
** File description:
** fg_no_args
*/

#include "mysh.h"
#include "builtins/fg.h"
#include "job_control.h"
#include "macro_errors.h"

int fg_no_args(mysh_t *mysh)
{
    pid_t pid = get_last_job_pgid(mysh->list);
    if (send_cont(pid) != SUCCESS) {
        mysh->last_status = FAILURE;
        return SUCCESS;
    }
    set_foreground(mysh, get_job_from_pid(mysh->list, pid), pid);
    return SUCCESS;
}
