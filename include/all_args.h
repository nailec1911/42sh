/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** all_args
*/

#ifndef ALL_ARGS_H_
    #define ALL_ARGS_H_

    #include "list_env.h"
    #include "parser/ast.h"

    typedef struct all_args_s {
        env_var_t *list_env;
        char **command;
        int last_status;
        int to_return;
        ast_t ast;
    } all_args_t;

#endif /* !ALL_ARGS_H_ */
