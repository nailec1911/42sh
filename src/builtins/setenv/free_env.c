/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** free_env
*/

#include <stdlib.h>
#include "all_args.h"

void free_env(all_args_t *all_args)
{
    env_var_t *to_free;
    env_var_t *temp = all_args->list_env;

    while (temp != NULL) {
        to_free = temp;
        temp = temp->next;
        free(to_free->var);
        free(to_free);
    }
}
