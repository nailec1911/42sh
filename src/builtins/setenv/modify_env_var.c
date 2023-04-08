/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** modify_env_var
*/

#include <stdlib.h>
#include "builtins/env.h"
#include "all_args.h"
#include "str_func.h"
#include "macro_errors.h"

int modify_env_var(char *to_change, all_args_t *all_args, char *new_value)
{
    char *new_var = NULL;
    int len_search = 0;
    env_var_t *temp = all_args->list_env;
    env_var_t *temp2 = all_args->list_env;

    if ((new_var = my_strcat_with_char(to_change, new_value, '=')) == NULL)
        return ERROR;
    len_search = my_strlen(all_args->command[1]) + 1;
    for (; temp != NULL; temp = temp->next) {
        if (my_strncmp(new_var, temp->var, len_search) == 0){
            free(temp->var);
            temp->var = new_var;
            return SUCCESS;
        }
    }
    if (put_elt_in_list(&temp2, new_var) == ERROR)
        return ERROR;
    all_args->list_env = temp2;
    return SUCCESS;
}
