/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** zzz
*/

#include <string.h>
#include "builtins/vars.h"
#include "mysh.h"
#include "macro_errors.h"
#include "parser/ast.h"

static int do_unset(vars_t *var, mysh_t *mysh)
{
    if (var->read_only) {
        fprintf(stderr, "unset: $%s is read-only.\n", var->name);
        return SUCCESS;
    }

    if (var->prev == 0) {
        mysh->vars = var->next;
        free_global_var(var);
        if (mysh->vars)
            mysh->vars->prev = 0;
    } else {
        var->prev->next = var->next;
        if (var->next)
            var->next->prev = var->prev;
        free_global_var(var);
    }

    return SUCCESS;
}

int do_unsetvar(mysh_t *mysh, command_t *to_exec)
{
    vars_t *var = 0;
    if (to_exec->args[1] == 0) {
        fprintf(stderr, "unset: Too few arguments.\n");
        return FAILURE;
    }

    for (int i = 1; to_exec->args[i] != 0; i++) {
        var = get_global_var_by_name(mysh->vars, to_exec->args[i]);
        if (!var)
            continue;

        do_unset(var, mysh);
    }

    return SUCCESS;
}
