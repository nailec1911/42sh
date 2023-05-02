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

static int print_env(mysh_t *mysh, command_t to_exec)
{
    vars_t *var = mysh->vars;
    char print_r = to_exec.command[1] && strcmp(to_exec.command[1], "-r") == 0;

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
    if (cmd[1] == 0)
        return SUCCESS;

    for (int i = 1; cmd[i] != 0; i++) {
        char ch = cmd[i][0];
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
    vars_t *var = create_global_var(buf, read_only);
    if (!var)
        return FAILURE;

    vars_t *existing = get_global_var_by_name(mysh->vars, var->name);
    if (existing != 0) {
        if (existing->read_only) {
            fprintf(stderr, "set: $%s is read-only.\n", var->name);
            return FAILURE;
        }
        edit_global_var(mysh->vars, var);
    }

    if (!existing)
        add_global_var(&mysh->vars, var);

    return SUCCESS;
}

int do_setvar(mysh_t *mysh, command_t to_exec)
{
    if (check_args(to_exec.command) != SUCCESS) {
        mysh->last_status = 1;
        return SUCCESS;
    }

    if ((mysh->command[1] == 0 || mysh->command[1][0] == 0) ||
            (strcmp(mysh->command[1], "-r") == 0 && mysh->command[2] == 0))
        return print_env(mysh, to_exec);

    char const read_only = strcmp(mysh->command[1], "-r") == 0;
    for (int i = read_only ? 2 : 1; to_exec.command[i] != 0; i++) {
        do_set(mysh, to_exec.command[i], read_only);
    }
    return 0;
}
