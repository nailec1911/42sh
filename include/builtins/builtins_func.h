/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** builtins
*/

#ifndef BUILTINS_H_
    #define BUILTINS_H_

    #include "mysh.h"

    int do_cd(mysh_t *mysh, command_t to_exec);
    int do_env(mysh_t *mysh, command_t to_exec);
    int do_exit(mysh_t *mysh, command_t to_exec);
    int do_setenv(mysh_t *mysh, command_t to_exec);
    int do_unsetenv(mysh_t *mysh, command_t to_exec);
    int do_history(mysh_t *mysh, command_t to_exec);
    int do_alias(mysh_t *mysh, command_t to_exec);
    int do_unalias(mysh_t *mysh, command_t to_exec);

    typedef struct builtin_s{
        char *command;
        int(*function)(mysh_t *mysh, command_t to_exec);
    } builtin_t;

    const struct builtin_s all_builtins[] = {
        {"cd", &do_cd},
        {"exit", &do_exit},
        {"env", &do_env},
        {"setenv", &do_setenv},
        {"unsetenv", &do_unsetenv},
        {"history", &do_history},
        {"alias", &do_alias},
        {"unalias", &do_unalias},
        {"\0", NULL}
    };

#endif /* !BUILTINS_H_ */
