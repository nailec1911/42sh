/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** builtins
*/

#ifndef BUILTINS_H_
    #define BUILTINS_H_

    #include "all_args.h"

    int do_cd(all_args_t *all_args, command_t to_exec);
    int do_env(all_args_t *all_args, command_t to_exec);
    int do_exit(all_args_t *all_args, command_t to_exec);
    int do_setenv(all_args_t *all_args, command_t to_exec);
    int do_unsetenv(all_args_t *all_args, command_t to_exec);

    typedef struct builtin_s{
        char *command;
        int(*function)(all_args_t *all_args, command_t to_exec);
    } builtin_t;

    const struct builtin_s all_builtins[] = {
        {"cd", &do_cd},
        {"exit", &do_exit},
        {"env", &do_env},
        {"setenv", &do_setenv},
        {"unsetenv", &do_unsetenv},
        {"\0", NULL}
    };

#endif /* !BUILTINS_H_ */
