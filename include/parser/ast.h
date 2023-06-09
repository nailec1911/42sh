/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** ast
*/

#ifndef AST_H_
    #define AST_H_

    #include <stdbool.h>
    #include <unistd.h>
    #include "parser/token.h"

    #define NO_REDIRECT 0

    typedef struct redirect_s {
        int type;
        char *name;
    } redirect_t;

    typedef enum status {
        RUNNING,
        DONE,
        SUSPENDED,
        CONTINUED,
        TERMINATED
    } status;

    typedef enum mode {
        FOREGROUND,
        BACKGROUND,
        PIPELINE
    } mode;

    typedef struct command_s {
        bool is_ast;
        struct ast_s *parenthesis;
        int nb_command;
        char **args;
        char *path;
        bool is_builtin;
        int fd_in;
        int fd_out;
        bool is_last;
        redirect_t redirect_in;
        redirect_t redirect_out;
        pid_t pid;
        status process_state;
    } command_t;

    typedef struct and_command_s {
        mode job_mode;
        int nb_command;
        command_t *tab_command;
        int job_id;
        pid_t pgid;
    } and_command_t;

    typedef struct or_command_s {
        int nb_and_command;
        and_command_t *tab_and_command;
    } or_command_t;

    typedef struct grocommand_s {
        int nb_or_command;
        or_command_t *tab_or_command;
    } grocommand_t;

    typedef struct ast_s {
        int nb_grocommand;
        grocommand_t *tab_grocommands;
    } ast_t;

    void free_ast(ast_t *ast);
#endif /* !AST_H_ */
