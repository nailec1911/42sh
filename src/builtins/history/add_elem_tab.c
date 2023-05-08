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
    int l_tab = history->len_tab_hist;
    tab_hist_t **temp = history->tab_hist;
    if ((history->tab_hist = malloc(sizeof(tab_hist_t *) *
    (l_tab + 2))) == NULL)
        return ERROR;
    history->tab_hist[l_tab + 1] = NULL;
    for (int i = 0; i < l_tab; i += 1) {
        history->tab_hist[i] = temp[i];
    }
    history->tab_hist[l_tab] = malloc(sizeof(tab_hist_t));
    history->tab_hist[l_tab]->num = num_to_str(num);
    if ((history->tab_hist[l_tab]->time = create_time_line()) == NULL)
        return ERROR;
    if ((history->tab_hist[l_tab]->command = strdup(to_add)) == NULL)
        return ERROR;
    if (temp != NULL)
        free(temp);
    history->len_tab_hist += 1;
    return SUCCESS;
}
