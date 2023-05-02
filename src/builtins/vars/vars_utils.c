/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** zzz
*/

#include <string.h>
#include <stdlib.h>
#include "builtins/vars.h"

void free_global_var(vars_t *var)
{
    free(var->name);
    free(var->buffer);
    free(var);
}

vars_t *get_global_var_by_name(vars_t *list, char *name)
{
    vars_t *tmp = list;

    for (; tmp; tmp = tmp->next) {
        if (strcmp(tmp->name, name) == 0)
            return tmp;
    }
    return 0;
}
