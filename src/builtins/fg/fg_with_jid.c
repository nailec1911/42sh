/*
** EPITECH PROJECT, 2023
** fg
** File description:
** fg_with_jid
*/

#include "mysh.h"
#include "builtins/fg.h"
#include "job_control.h"
#include "macro_errors.h"
#include "parser/ast.h"

int fg_with_jid(mysh_t *mysh, int job_id)
{
    pid_t pid;
    and_command_t *tmp = NULL;

    if (job_id > (mysh->nb_current_job - 1) ||
            !(tmp = get_job_from_id(mysh->list, job_id))) {
        fprintf(stderr, "fg: No such job.\n");
        mysh->last_status = FAILURE;
        return SUCCESS;
    }
    pid = tmp->pgid;
    if (send_cont(pid) != SUCCESS) {
        mysh->last_status = FAILURE;
        return SUCCESS;
    }
    set_foreground(mysh, tmp, pid);
    return SUCCESS;
}
