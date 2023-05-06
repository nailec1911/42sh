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
        return display_alias(mysh->alias, to_exec.fd_out, to_exec.args);
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

static char *check_is_alias(char **tab_alias, char *input, char *to_search)
{
    char *res = input;

    if (tab_alias == NULL || to_search == NULL)
        return NULL;
    if (tab_alias[2] == NULL)
        return input;
    if (strcmp(to_search, tab_alias[1]) == 0) {
        if ((res = clean_last_input(tab_alias)) == NULL)
            return NULL;
        free(input);
    }
    free_array(tab_alias);
    return res;
}

char *is_alias(alias_t *alias, char *input)
{
    char **tab_alias = NULL;
    char *res = NULL;

    if (alias == NULL || input == NULL)
        return NULL;
    if (alias->tab_file == NULL)
        return NULL;
    for (int i = 0; alias->tab_file[i] != NULL; i += 1) {
        tab_alias = my_str_to_word_array_separator
        (alias->tab_file[i], " \n");
        if (tab_alias == NULL)
            return NULL;
        res = check_is_alias(tab_alias, res, input);
    }
    return res;
}
