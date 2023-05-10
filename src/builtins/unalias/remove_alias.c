/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "mysh.h"
#include "str_func.h"
#include "macro_errors.h"
#include <unistd.h>

static void write_in_file_alias(alias_t *alias)
{
    for (int i = 0; alias->tab_file[i] != NULL; i += 1) {
        dprintf(alias->fd_alias_file, "%s", alias->tab_file[i]);
    }
}

static int nb_elem_to_remove(char **tab, char *to_find)
{
    char **tab_alias = NULL;
    int nb_elem = 0;

    for (int i = 0; tab[i] != NULL; i += 1) {
        tab_alias = my_str_to_word_array_separator(tab[i], " \n");
        if (strcmp(tab_alias[1], to_find) == 0)
            nb_elem += 1;
        free_array(tab_alias);
    }
    return nb_elem;
}

static char **fill_tab_without_alias(alias_t *alias, char **new_tab,
char *to_compare)
{
    int index = 0;
    char **tab_alias = NULL;

    for (int i = 0; alias->tab_file[i] != NULL; i += 1) {
        tab_alias = my_str_to_word_array_separator
        (alias->tab_file[i], " \n");
        if (strcmp(tab_alias[1], to_compare) != 0) {
            new_tab[index] = strdup(alias->tab_file[i]);
            index += 1;
        } else {
            free(alias->tab_file[i]);
        }
        free_array(tab_alias);
    }
    free(alias->tab_file);
    return new_tab;
}

static int remove_alias(alias_t *alias, char *command)
{
    char **new_tab = NULL;
    int l_tab = 0;
    int nb_elem = 0;

    l_tab = length_tab(alias->tab_file);
    nb_elem = nb_elem_to_remove(alias->tab_file, command);
    if ((new_tab = malloc(sizeof(char *) * (l_tab - nb_elem + 1))) == NULL)
        return ERROR;
    new_tab[l_tab - nb_elem] = NULL;
    alias->tab_file = fill_tab_without_alias(alias, new_tab, command);
    if (alias->tab_file == NULL)
        return ERROR;
    return SUCCESS;
}

int do_unalias(mysh_t *mysh, command_t *to_exec)
{
    int l_args = length_tab(to_exec->args);

    if (l_args == 1) {
        fprintf(stderr, "unalias: Too few arguments.\n");
        mysh->last_status = 1;
        return SUCCESS;
    }
    if (mysh->alias.tab_file == NULL || mysh->alias.tab_file[0] == NULL)
        return SUCCESS;
    for (int i = 1; to_exec->args[i] != NULL; i += 1) {
        if (remove_alias(&mysh->alias, to_exec->args[i]) == ERROR)
            return ERROR;
    }
    if (mysh->alias.fd_alias_file != -1) {
        if (ftruncate(mysh->alias.fd_alias_file, 0) == -1)
            return ERROR;
        write_in_file_alias(&mysh->alias);
    }
    return SUCCESS;
}
