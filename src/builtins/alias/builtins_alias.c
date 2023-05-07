/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "mysh.h"
#include "alias.h"
#include "str_func.h"
#include "macro_errors.h"
#include "init.h"

static int add_alias_rc(alias_t *alias, char *input)
{
    int l_tab = 0;
    if (alias->tab_file == NULL) {
        if ((alias->tab_file = malloc(sizeof(char *) * 2)) == NULL)
            return ERROR;
        alias->tab_file[0] = input;
        alias->tab_file[1] = NULL;
        if (alias->have_alias == false)
            return SUCCESS;
        dprintf(alias->fd_alias_file, "%s", alias->tab_file[0]);
    } else {
        if (add_elem_tab_alias(alias, input) == ERROR)
            return ERROR;
        l_tab = length_tab(alias->tab_file);
        if (alias->have_alias == false)
            return SUCCESS;
        dprintf(alias->fd_alias_file, "%s", alias->tab_file[l_tab - 1]);
    }
    return SUCCESS;
}

int do_alias(mysh_t *mysh, command_t to_exec)
{
    char *command = NULL;
    if (to_exec.args[1] == NULL) {
        if (mysh->alias.tab_file == NULL)
            return SUCCESS;
        return display_alias(mysh->alias, to_exec.fd_out);
    }
    if (to_exec.args[2] == NULL) {
        if (mysh->alias.tab_file == NULL)
            return SUCCESS;
        return display_specific_alias
        (mysh->alias, to_exec.args[1], to_exec.fd_out);
    } else {
        command = remake_input(to_exec.args);
        if (add_alias_rc(&mysh->alias, command) == ERROR) {
            mysh->last_status = 1;
            return ERROR;
        }
    }
    return SUCCESS;
}
