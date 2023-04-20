/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** launch_command
*/

#ifndef LAUNCH_COMMAND_H_
    #define LAUNCH_COMMAND_H_

    #include "all_args.h"

    char *get_input(void);
    char *get_input_line(void);
    int go_throught_grocommand(all_args_t *all_args);
    int parse_input(char *input, all_args_t *all_args);
    void free_ast(ast_t ast);

#endif /* !LAUNCH_COMMAND_H_ */
