/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** handle_input
*/

#ifndef HANDLE_INPUT_H_
    #define HANDLE_INPUT_H_

    #include "all_args.h"

    int try_command_with_path(all_args_t *all_args);
    int handle_input(all_args_t *all_args);
    int get_path(all_args_t *all_args, char **path);

#endif /* !HANDLE_INPUT_H_ */
