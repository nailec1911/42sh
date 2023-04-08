/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** exec_command
*/

#ifndef EXEC_COMMAND_H_
    #define EXEC_COMMAND_H_

    #include "all_args.h"

    int exec_command(all_args_t *all_args, command_t to_exec);
    int exec_builtins(all_args_t *all_args, command_t to_exec);
    int handle_errors(int status);
    int set_fd_input(command_t *command);
    int set_fd_output(command_t *command);
    int handle_errors(int status);
    int exec_builtins(all_args_t *all_args, command_t to_exec);
    int get_path(all_args_t *all_args, char **path);

#endif /* !EXEC_COMMAND_H_ */
