/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** put_in_list
*/

#include <stdlib.h>
#include "list_env.h"
#include "macro_errors.h"

int put_elt_in_list(env_var_t **list, char *str)
{
    env_var_t *new = NULL;
    env_var_t *temp = *list;

    if ((new = malloc(sizeof(*new))) == NULL)
        return ERROR;
    new->var = str;
    new->next = NULL;
    if (*list == NULL) {
        *list = new;
        return SUCCESS;
    }
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new;
    return SUCCESS;
}
