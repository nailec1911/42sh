/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** launch_command
*/

#ifndef LAUNCH_COMMAND_H_
    #define LAUNCH_COMMAND_H_

    #include "mysh.h"

    char *get_input(mysh_t mysh);
    char *get_input_line(void);
    void free_ast(ast_t *ast);

#endif /* !LAUNCH_COMMAND_H_ */
