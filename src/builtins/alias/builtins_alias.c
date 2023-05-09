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

static int add_elem_tab_alias(alias_t *alias, char *to_add)
{
    int len_tab = 0;
    char **temp = alias->tab_file;

    if (!alias || !to_add)
        return ERROR;
    len_tab = length_tab(alias->tab_file);
    alias->tab_file = malloc(sizeof(char *) * (len_tab + 2));
    if (!alias->tab_file)
        return ERROR;
    alias->tab_file[len_tab + 1] = NULL;
    for (int i = 0; i < len_tab; i += 1) {
        alias->tab_file[i] = temp[i];
    }
    alias->tab_file[len_tab] = to_add;
    if (temp != NULL)
        free(temp);
    return SUCCESS;
}

static int add_alias_rc(alias_t *alias, char *input)
{
    if (!alias || !input)
        return ERROR;
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
        if (alias->have_alias == false)
            return SUCCESS;
        dprintf(alias->fd_alias_file, "%s",
        alias->tab_file[length_tab(alias->tab_file) - 1]);
    }
    return SUCCESS;
}

static int display_alias_or_specific(mysh_t *mysh, char **args, int fd_out)
{
    if (mysh->alias.tab_file == NULL)
        return SUCCESS;
    if (args == NULL || args[1] == NULL) {
        return display_alias(mysh->alias.tab_file, fd_out);
    }
    if (args[2] == NULL) {
        return display_specific_alias(mysh->alias.tab_file, args[1], fd_out);
    }
    return SUCCESS;
}

int do_alias(mysh_t *mysh, command_t to_exec)
{
    char *command = NULL;

    if (!mysh || !to_exec.args || !to_exec.args[0])
        return ERROR;
    if (to_exec.args[1] == NULL || to_exec.args[2] == NULL) {
        return display_alias_or_specific(mysh, to_exec.args, to_exec.fd_out);
    } else {
        command = remake_input(to_exec.args);
        if (command == NULL || add_alias_rc(&mysh->alias, command) == ERROR)
            return ERROR;
    }
    return SUCCESS;
}
