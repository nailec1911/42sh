/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** zzz
*/

#include <stdlib.h>
#include <string.h>
#include "builtins/vars.h"

static char *get_var_name_from_buf(char *buf)
{
    int i = 0;
    char *name = 0;

    for (; buf[i] != '=' && buf[i] != 0; i++);
    name = malloc(sizeof(char) * (i + 1));
    if (!name)
        return 0;
    for (int j = 0; j < i; j++)
        name[j] = buf[j];
    name[i] = 0;
    return name;
}

static char *get_var_value_from_buf(char *buf)
{
    int i = 0;

    for (; buf[i] != '=' && buf[i] != 0; i++);
    if (buf[i] == 0)
        return 0;
    return strdup(&buf[i + 1]);
}

vars_t *edit_global_var(vars_t *list, vars_t *new_var)
{
    vars_t *existing_var = get_global_var_by_name(list, new_var->name);
    if (!existing_var)
        return 0;

    free(existing_var->name);
    free(existing_var->buffer);
    existing_var->name = new_var->name;
    existing_var->buffer = new_var->buffer;
    existing_var->read_only = new_var->read_only;
    free(new_var);
    return existing_var;
}

vars_t *create_global_var(char *buffer, char read_only)
{
    vars_t *new_var = malloc(sizeof(vars_t));

    if (!new_var || !buffer)
        return 0;

    char *buf_name = get_var_name_from_buf(buffer);
    char *buf_value = get_var_value_from_buf(buffer);
    new_var->name = buf_name;
    new_var->buffer = buf_value;
    new_var->read_only = read_only;
    new_var->next = 0;
    new_var->prev = 0;
    return new_var;
}

void add_global_var(vars_t **list, vars_t *new_var)
{
    if (!list)
        return;

    vars_t *tmp = *list;

    if (!tmp) {
        *list = new_var;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_var;
    tmp->next->prev = tmp;
}
