/*
** EPITECH PROJECT, 2023
** fg
** File description:
** fg_with_pid
*/

#include "mysh.h"
#include "builtins/fg.h"
#include "job_control.h"
#include "macro_errors.h"
#include "parser/ast.h"

int fg_with_pid(mysh_t *mysh, pid_t pid)
{
    if (!mysh)
        return ERROR;
    if (send_cont(pid) != SUCCESS) {
        mysh->last_status = FAILURE;
        return SUCCESS;
    }
    set_foreground(mysh, get_job_from_pid(mysh->list, pid), pid);
    return SUCCESS;
}
