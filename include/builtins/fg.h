/*
** EPITECH PROJECT, 2023
** FG_H_
** File description:
** fg
*/

#include "mysh.h"
#include "job_control.h"

#ifndef FG_H_
    #define FG_H_

    int do_fg(mysh_t *mysh, command_t *to_exec);
    int send_cont(pid_t pid);
    void set_foreground(mysh_t *mysh, and_command_t *job, pid_t pid);
    int fg_no_args(mysh_t *mysh);
    int fg_with_jid(mysh_t *mysh, int job_id);
    int fg_with_pid(mysh_t *mysh, pid_t pid);

#endif /* FG_H_ */
