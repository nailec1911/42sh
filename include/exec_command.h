/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** exec_command
*/

#ifndef EXEC_COMMAND_H_
    #define EXEC_COMMAND_H_

    #include "mysh.h"

    int exec_and_command(mysh_t *mysh, and_command_t *to_exec);
    int exec_command(mysh_t *mysh, command_t to_exec);
    int exec_builtins(mysh_t *mysh, command_t to_exec);
    int handle_errors(int status);
    int set_fd_input(command_t *command);
    int set_fd_output(command_t *command);
    int handle_errors(int status);
    int get_path(mysh_t *mysh, char **path);

#endif /* !EXEC_COMMAND_H_ */
