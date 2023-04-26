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

int add_elem_tab(history_t *history, char *to_add, int num)
{
    int len_tab = length_tab_hist(history->tab_hist);
    tab_hist_t **temp = history->tab_hist;
    if ((history->tab_hist = malloc(sizeof(tab_hist_t *) *
    (len_tab + 2))) == NULL)
        return ERROR;
    history->tab_hist[len_tab + 1] = NULL;
    for (int i = 0; i < len_tab; i += 1) {
        history->tab_hist[i] = temp[i];
    }
    history->tab_hist[len_tab] = malloc(sizeof(tab_hist_t));
    history->tab_hist[len_tab]->num = num_to_str(num);
    if ((history->tab_hist[len_tab]->time = create_time_line()) == NULL)
        return ERROR;
    if ((history->tab_hist[len_tab]->command = strdup(to_add)) == NULL)
        return ERROR;
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
