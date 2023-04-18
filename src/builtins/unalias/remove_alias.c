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
#include "macro_errors.h"
#include <unistd.h>

static void write_in_file(mysh_t *mysh)
{
    for (int i = 0; mysh->alias->tab_file[i] != NULL; i += 1) {
        fprintf(mysh->alias->fd_file, "%s", mysh->alias->tab_file[i]);
    }
    fflush(mysh->alias->fd_file);
}

static int nb_elem_to_remove(char **tab, char *to_find)
{
    char **tab_alias = NULL;
    int nb_elem = 0;

    for (int i = 0; tab[i] != NULL; i += 1) {
        tab_alias = my_str_to_word_array_separator(tab[i], " \n");
        if (strcmp(tab_alias[1], to_find) == 0)
            nb_elem += 1;
    }
    return nb_elem;
}

static char **fill_tab_without_alias(mysh_t *mysh, char **new_tab,
char *to_compare)
{
    int index = 0;
    char **tab_alias = NULL;

    for (int i = 0; mysh->alias->tab_file[i + 1] != NULL; i += 1) {
        tab_alias = my_str_to_word_array_separator
        (mysh->alias->tab_file[i], " \n");
        if (strcmp(tab_alias[1], to_compare) != 0) {
            free(new_tab[index]);
            new_tab[index] = strdup(mysh->alias->tab_file[i]);
            index += 1;
        }
    }
    return new_tab;
}

int do_unalias(mysh_t *mysh, command_t to_exec)
{
    char **new_tab = NULL;
    int nb_elem = 0;
    int l_tab = 0;

    if (mysh->alias->tab_file == NULL || mysh->alias->tab_file[0] == NULL)
        return SUCCESS;
    l_tab = length_tab(mysh->alias->tab_file);
    nb_elem = nb_elem_to_remove(mysh->alias->tab_file, to_exec.command[1]);
    if ((new_tab = malloc(sizeof(char *) * (l_tab - nb_elem + 1))) == NULL)
        return ERROR;
    new_tab[l_tab - nb_elem] = NULL;
    mysh->alias->tab_file = fill_tab_without_alias
    (mysh, new_tab, to_exec.command[1]);
    if (ftruncate(mysh->alias->fd_alias_file, 0) == -1) {
        return ERROR;
    }
    write_in_file(mysh);
    return SUCCESS;
}
