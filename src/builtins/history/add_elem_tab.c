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

static int resize_tab_history(history_t *history)
{
    int l_tab = history->len_tab_hist;
    tab_hist_t **temp = history->tab_hist;

    history->tab_hist = calloc(l_tab + 1, sizeof(tab_hist_t *));
    if (history->tab_hist == NULL)
        return ERROR;
    for (int i = 0; i < l_tab - 1; i += 1) {
        history->tab_hist[i] = temp[i];
    }
    if (temp != NULL)
        free(temp);
    return SUCCESS;
}

static int fill_new_elt(tab_hist_t *new, char *to_add, int num)
{
    if (!new || !to_add)
        return ERROR;
    new->num = num_to_str(num);
    new->time = create_time_line();
    new->command = strdup(to_add);
    if (!new->num || !new->time || !new->command)
        return ERROR;
    return SUCCESS;
}

int add_elem_tab(history_t *history, char *to_add, int num)
{
    int l_tab = 0;

    if (!history || !to_add || history->len_tab_hist < 0)
        return ERROR;
    history->len_tab_hist += 1;
    if (resize_tab_history(history) == ERROR)
        return ERROR;
    l_tab = history->len_tab_hist;
    history->tab_hist[l_tab - 1] = malloc(sizeof(tab_hist_t));
    if (!history->tab_hist[l_tab - 1])
        return ERROR;
    return fill_new_elt(history->tab_hist[l_tab - 1], to_add, num);
}
