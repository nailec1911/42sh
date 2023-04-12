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

    typedef struct mysh_s {
        env_var_t *list_env;
        char **command;
        int last_status;
        int to_return;
        ast_t ast;
    } mysh_t;

#endif /* !MYSH_H_ */
