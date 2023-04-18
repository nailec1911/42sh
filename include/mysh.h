/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** mysh
*/

#ifndef MYSH_H_
    #define MYSH_H_

    #include "list_env.h"
    #include "parser/ast.h"
    #include "alias.h"
    #include "history.h"

    typedef struct mysh_s {
        env_var_t *list_env;
        char **command;
        int last_status;
        int to_return;
        ast_t ast;
        history_t *history;
        alias_t *alias;
    } mysh_t;

char *create_line_history(mysh_t *mysh, char *input);
int check_last_command(mysh_t *mysh, char *input);
int init_alias(mysh_t *mysh);
int is_alias(mysh_t *mysh, char **input);
#endif /* !MYSH_H_ */
