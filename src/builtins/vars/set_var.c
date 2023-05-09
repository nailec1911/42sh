/*
** EPITECH PROJECT, 2023
** 42SH
** File description:
** zz
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "builtins/vars.h"
#include "mysh.h"
#include "macro_errors.h"
#include "str_func.h"

static int print_env(mysh_t *mysh, command_t to_exec)
{
    vars_t *var = mysh->vars;
    char print_r = to_exec.args[1] && strcmp(to_exec.args[1], "-r") == 0;

    for (; var; var = var->next) {
        if ((print_r && !var->read_only) || (!print_r && var->read_only))
            continue;
        dprintf(to_exec.fd_out, "%s\t%s\n", var->name, var->buffer ?
                var->buffer : "");
    }
    return SUCCESS;
}

static int check_args(char **cmd)
{
    char ch = '\0';

    if (cmd[1] == 0)
        return SUCCESS;
    for (int i = 1; cmd[i] != 0; i++) {
        ch = cmd[i][0];
        if (i == 1 && strcmp(cmd[i], "-r") == 0)
            continue;
        if (!(ch >= 'a' && ch <= 'z') && !(ch >= 'A' && ch <= 'Z')) {
            fprintf(stderr, "set: Variable name must begin with a letter.\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}

static int do_set(mysh_t *mysh, char *buf, char const read_only)
{
    vars_t *existing = NULL;
    vars_t *var = create_global_var(buf, read_only);

    if (!var || !mysh)
        return FAILURE;
    existing = get_global_var_by_name(mysh->vars, var->name);
    if (existing != 0) {
        if (existing->read_only) {
            mysh->last_status = 1;
            fprintf(stderr, "set: $%s is read-only.\n", var->name);
            return FAILURE;
        }
        edit_global_var(mysh->vars, var);
    }
    if (!existing)
        add_global_var(&mysh->vars, var);

    return SUCCESS;
}

static int set_all_vars(mysh_t *mysh, command_t *to_exec, char **new_args)
{
    char const read_only = strcmp(to_exec->args[1], "-r") == 0;

    for (int i = read_only ? 2 : 1; new_args[i] != 0; i++)
        do_set(mysh, new_args[i], read_only);
    free_array(new_args);
    return 0;
}

int do_setvar(mysh_t *mysh, command_t to_exec)
{
    char **new_args = NULL;

    if (!mysh)
        return ERROR;
    new_args = recreate_args(to_exec.args);
    if (!new_args)
        return FAILURE;
    if (check_args(new_args) != SUCCESS) {
        mysh->last_status = 1;
        free_array(new_args);
        return SUCCESS;
    }
    if ((to_exec.args[1] == 0 || to_exec.args[1][0] == 0) ||
            (strcmp(to_exec.args[1], "-r") == 0 && to_exec.args[2] == 0)) {
        free_array(new_args);
        return print_env(mysh, to_exec);
    }
    return set_all_vars(mysh, &to_exec, new_args);
}
