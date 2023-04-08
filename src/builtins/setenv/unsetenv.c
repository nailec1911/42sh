/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** unset_env
*/

#include <stdlib.h>
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"

static void remove_first(env_var_t **list)
{
    env_var_t *to_free = *list;

    (*list) = (*list)->next;
    free(to_free->var);
    free(to_free);
}

static int remove_from_env
(all_args_t *all_args, int len_search, char *to_remove)
{
    env_var_t *temp = all_args->list_env;
    env_var_t *to_free = temp;

    if (my_strncmp(to_remove, all_args->list_env->var, len_search) == 0
    && all_args->list_env->var[len_search] == '='){
        remove_first(&temp);
        all_args->list_env = temp;
    }
    temp = all_args->list_env;
    while (temp != NULL && temp->next != NULL){
        if (my_strncmp(to_remove, (temp)->next->var, len_search) == 0
        && (temp)->next->var[len_search] == '='){
            to_free = temp->next;
            (temp)->next = (temp)->next->next;
            free(to_free->var);
            free(to_free);
        }
        temp = temp->next;
    }
    return SUCCESS;
}

int do_unsetenv(all_args_t *all_args, command_t to_exec)
{
    int len_search = 0;

    if (to_exec.command[1] == NULL) {
        my_putstr("unsetenv: Too few arguments.\n", 2);
        all_args->last_status = 1;
        return SUCCESS;
    }
    if (all_args->list_env == NULL)
        return SUCCESS;
    for (int i = 1; to_exec.command[i] != NULL; i += 1) {
        len_search = my_strlen(to_exec.command[i]);
        remove_from_env(all_args, len_search, to_exec.command[i]);
    }
    return SUCCESS;
}
