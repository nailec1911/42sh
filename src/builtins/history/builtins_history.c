/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <string.h>
#include <stdlib.h>
#include "mysh.h"
#include "str_func.h"
#include "macro_errors.h"
int detect_flags(command_t *to_exec, history_t *history);

int opt_clear(mysh_t *mysh)
{
    tab_hist_t **tab = malloc(sizeof(tab_hist_t *) * 2);
    int l_tab = mysh->history.len_tab_hist;
    tab_hist_t **to_free = mysh->history.tab_hist;
    if (tab == NULL)
        return ERROR;
    tab[0] = malloc(sizeof(tab_hist_t));
    if (tab[0] == NULL)
        return ERROR;
    tab[0]->num = strdup(mysh->history.tab_hist[l_tab - 1]->num);
    tab[0]->time = strdup(mysh->history.tab_hist[l_tab - 1]->time);
    tab[0]->command = strdup(mysh->history.tab_hist[l_tab - 1]->command);
    tab[1] = NULL;
    mysh->history.len_tab_hist = 1;
    mysh->history.tab_hist = tab;
    free_tab_hist(to_free);
    return SUCCESS;
}

static int init_flag(history_t *history, int *step, int *i)
{
    int end = history->len_tab_hist;
    if (IS_FLAG(history->flags, FLAG_R)) {
        *step = -1;
        end = -1;
        *i = history->len_tab_hist - 1;
    }
    return end;
}

int display_history(tab_hist_t **tab, int fd, history_t *history)
{
    char *time = create_time_line();
    char *num = num_to_str(history->num_command);
    int i = 0;
    int step = 1;
    int end = init_flag(history, &step, &i);
    for (; i != end; i += step) {
        if (IS_FLAG(history->flags, FLAG_H))
            dprintf(fd, "%s", tab[i]->command);
        else
            dprintf(fd, "%s  %s   %s", tab[i]->num, tab[i]->time,
            tab[i]->command);
    }
    if (history->flags == NO_FLAG)
        dprintf(fd, "%s  %s   %s\n", num, time, "history");
    free(num);
    free(time);
    return SUCCESS;
}

int do_history(mysh_t *mysh, command_t to_exec)
{
    if (to_exec.command[1] == NULL) {
        mysh->history.flags = NO_FLAG;
        return display_history(mysh->history.tab_hist, to_exec.fd_out,
        &mysh->history);
    }
    mysh->history.flags = NO_FLAG;
    if (detect_flags(&to_exec, &mysh->history) == ERROR) {
        printf("Usage: history [-chrSLMT] [# number of events].\n");
        mysh->last_status = 1;
        return SUCCESS;
    }
    if (IS_FLAG(mysh->history.flags, FLAG_C))
        opt_clear(mysh);
    else
        display_history(mysh->history.tab_hist, to_exec.fd_out, &mysh->history);
    return SUCCESS;
}
