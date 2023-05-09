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

static int replace_last_line(history_t *history, char *input)
{
    int l_tab = 0;

    if (!history || !input)
        return ERROR;
    l_tab = history->len_tab_hist;
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
    return SUCCESS;
}

static int add_line_history(history_t *history, char *input)
{
    if (!history || !input)
        return ERROR;
    if (strcmp
    (input,history->tab_hist[history->len_tab_hist - 1]->command) == 0) {
        return replace_last_line(history, input);
    } else {
        if (add_elem_tab(history, input, history->num_cmd) == ERROR)
            return ERROR;
    }
    return SUCCESS;
}

int check_last_command(history_t *history, char *input)
{
    if (!history || !input)
        return ERROR;
    if (!history->tab_hist || history->have_hist == false
    || !history->tab_hist[0]) {
        if (add_elem_tab(history, input, history->num_cmd) == ERROR)
            return ERROR;
        history->len_tab_hist = 1;
    } else {
        if (add_line_history(history, input) == ERROR)
            return ERROR;;
    }
    write_in_file
    (history->tab_hist, history->fd_history_file, history->have_hist);
    return SUCCESS;
}
