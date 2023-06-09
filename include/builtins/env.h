/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** env
*/

#ifndef ENV_H_
    #define ENV_H_

    #include "mysh.h"

    char **init_mysh_env(char * const env[]);
    int do_env(mysh_t *mysh, command_t *command);
    char *get_env_var(mysh_t *mysh, char *var);
    int modify_env_var(char *to_change, mysh_t *mysh, char *new_value);
    void free_env(mysh_t *mysh);

#endif /* !ENV_H_ */
