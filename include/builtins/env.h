/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** env
*/

#ifndef ENV_H_
    #define ENV_H_

    #include "list_env.h"
    #include "mysh.h"

    env_var_t *create_list_env(char * const env[]);
    int put_elt_in_list(env_var_t **list, char *str);
    char **set_new_env(env_var_t *env_list);
    int modify_env_var(char *to_change, mysh_t *mysh, char *new_value);
    int do_env(mysh_t *mysh, command_t command);
    char *get_env_var(env_var_t *list_env, char *var);
    void free_env(mysh_t *mysh);
    int put_elt_in_list(env_var_t **list, char *str);
    char *my_str_dup(char const *src);

#endif /* !ENV_H_ */
