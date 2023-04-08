/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** ast
*/

#ifndef AST_H_
    #define AST_H_

    #include <stdbool.h>
    #include "parser/token.h"

    typedef enum {
        NO_REDIRECT,
        IN_1,
        IN_2,
        OUT_1,
        OUT_2
    } type_redirect_t;

    typedef struct redirect_s {
        type_redirect_t type;
        char *name;
    } redirect_t;

    typedef struct command_s {
        int nb_command;
        char **command;
        char *to_exec;
        bool is_builtin;
        int fd_in;
        int fd_out;
        bool is_last;
        redirect_t redirect_in;
        redirect_t redirect_out;
    } command_t;

    typedef struct grocommand_s {
        int nb_command;
        command_t *tab_command;
    } grocommand_t;

    typedef struct ast_s {
        int nb_grocommand;
        grocommand_t *tab_grocommands;
    } ast_t;

    typedef struct parser_s {
        token_t *list_tokens;
        int cursor;
        int error;
    } parser_t;

#endif /* !AST_H_ */
