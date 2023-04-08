/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** list_env
*/

#ifndef LIST_ENV_H_
    #define LIST_ENV_H_

    typedef struct env_var_s{
        char *var;
        struct env_var_s *next;
    } env_var_t;

#endif /* !LIST_ENV_H_ */
