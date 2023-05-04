/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include "mysh.h"
#include <unistd.h>
#include "macro_errors.h"
#include "history.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "str_func.h"

void write_in_file(tab_hist_t **tab, int fd, bool have_file)
{
    if (have_file == false)
        return;
    for (int i = 0; tab[i] != NULL; i += 1) {
        dprintf(fd, "%s  %s   %s", tab[i]->num, tab[i]->time, tab[i]->command);
    }
}

int replace_last_line(history_t *history, char *input)
{
    int l_tab = history->len_tab_hist;

    free(history->tab_hist[l_tab - 1]->num);
    free(history->tab_hist[l_tab - 1]->time);
    free(history->tab_hist[l_tab - 1]->command);
    history->tab_hist[l_tab - 1]->num = num_to_str(history->num_cmd);
    history->tab_hist[l_tab - 1]->time = create_time_line();
    history->tab_hist[l_tab - 1]->command = strdup(input);
    if (history->tab_hist[l_tab - 1]->command == NULL ||
    history->tab_hist[l_tab - 1]->num == NULL ||
    history->tab_hist[l_tab - 1]->time == NULL)
        return ERROR;
    write_in_file(history->tab_hist, history->fd_history_file, history->have_hist);
    return SUCCESS;
}

int add_line(history_t *history, char *input)
{
    if (add_elem_tab(history, input,
    history->num_cmd) == ERROR)
        return ERROR;
    write_in_file(history->tab_hist, history->fd_history_file, history->have_hist);
    return SUCCESS;
}

int add_line_history(history_t *history, char *input)
{
    int l_tab = history->len_tab_hist;
    if (strcmp(input,history->tab_hist[l_tab - 1]->command) == 0) {
        return replace_last_line(history, input);
    } else {
        return add_line(history, input);
    }
}

int check_last_command(history_t *history, char *input)
{
    if (history->tab_hist == NULL || history->have_hist == false) {
        if ((history->tab_hist = malloc(sizeof(tab_hist_t *) * 2)) == NULL)
            return ERROR;
        if ((history->tab_hist[0] = malloc(sizeof(tab_hist_t))) == NULL)
            return ERROR;
        if ((history->tab_hist[0]->num = num_to_str(history->num_cmd)) == NULL)
            return ERROR;
        if ((history->tab_hist[0]->time = create_time_line()) == NULL)
            return ERROR;
        if ((history->tab_hist[0]->command = strdup(input)) == NULL)
            return ERROR;
        history->tab_hist[1] = NULL;
        history->len_tab_hist = 1;
        write_in_file(history->tab_hist, history->fd_history_file, history->have_hist);
    } else {
        return add_line_history(history, input);
    }
    return SUCCESS;
}
