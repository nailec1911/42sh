/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** exec_command
*/

#ifndef EXEC_COMMAND_H_
    #define EXEC_COMMAND_H_

    #include "mysh.h"

    int loop_grocommand(mysh_t *mysh, ast_t *ast);
    int set_and_command(mysh_t *mysh, and_command_t *to_exec);
    int exec_parenthesis(mysh_t *mysh, command_t *to_exec);
    int exec_process
    (mysh_t *mysh, and_command_t *job, command_t *process, bool pipe);
    int exec_builtins(mysh_t *mysh, command_t to_exec);
    int handle_errors(int status);
    int set_fd_input(command_t *command);
    int set_fd_output(command_t *command);
    int get_path(mysh_t *mysh, char **path, command_t *to_exec);
    int set_magic_quote(mysh_t *mysh, and_command_t *actual);
    void display_error_exec(int error_code, char *path);

#endif /* !EXEC_COMMAND_H_ */
