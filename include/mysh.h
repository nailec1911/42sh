/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** mysh
*/

#ifndef MYSH_H_
    #define MYSH_H_

    #include <stdbool.h>
    #include "parser/ast.h"
    #include "alias.h"
    #include "history.h"
    #include "builtins/vars.h"
    #include "tab.h"
    #include "job_control.h"

    typedef struct mysh_s {
        vars_t *vars;
        char **command;
        char **env;
        int last_status;
        int to_return;
        bool tab;
        bool enter;
        bool first_tab;
        int ch;
        int ind_history;
        int ind_init;
        tab_t completion;
        ast_t ast;
        bool display_line;
        history_t history;
        alias_t alias;

        pid_t shell_pgid;
        short shell_descriptor;
        job_list *list;
        int nb_current_job;
    } mysh_t;


    //history
    int check_last_command(history_t *history, char *input);
    int init_alias(alias_t *alias);

    //job control
    int exec_job(mysh_t *mysh, and_command_t *job);

    int loop_sh(mysh_t *mysh, char *input);

#endif /* !MYSH_H_ */
