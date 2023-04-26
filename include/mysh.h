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

    typedef struct mysh_s {
        char **env;
        char **command;
        int last_status;
        int to_return;
        bool tty;
        int ch;
        int ind_history;
        int ind_init;
        ast_t ast;
        bool display_line;
        history_t history;
        alias_t alias;
    } mysh_t;

int check_last_command(history_t *history, char *input);
int init_alias(alias_t *alias);
#endif /* !MYSH_H_ */
