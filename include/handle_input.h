/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** handle_input
*/

#ifndef HANDLE_INPUT_H_
    #define HANDLE_INPUT_H_

    #include "mysh.h"

    int try_command_with_path(mysh_t *mysh);
    int handle_input(mysh_t *mysh);
    int get_path(mysh_t *mysh, char **path);

#endif /* !HANDLE_INPUT_H_ */
