/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include "mysh.h"
#include "history.h"
#include "macro_errors.h"
#include "alias.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int add_elem_tab(history_t *history, char *to_add)
{
    int len_tab = length_tab(history->tab_file);
    char **temp = history->tab_file;

    if ((history->tab_file = malloc(sizeof(char *) * (len_tab + 2))) == NULL)
        return ERROR;
    history->tab_file[len_tab + 1] = NULL;
    for (int i = 0; i < len_tab; i += 1) {
        history->tab_file[i] = temp[i];
    }
    history->tab_file[len_tab] = to_add;
    if (temp != NULL)
        free(temp);
    return SUCCESS;
}

int add_elem_tab_alias(alias_t *alias, char *to_add)
{
    int len_tab = length_tab(alias->tab_file);
    char **temp = alias->tab_file;

    if ((alias->tab_file = malloc(sizeof(char *) * (len_tab + 2))) == NULL)
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
