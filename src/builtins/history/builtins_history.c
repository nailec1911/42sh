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

int opt_clear(mysh_t *mysh)
{
    tab_hist_t **tab = malloc(sizeof(tab_hist_t *) * 2);
    int l_tab = length_tab_hist(mysh->history.tab_hist);
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
    mysh->history.tab_hist = tab;
    free_tab_hist(to_free);
    return SUCCESS;
}

int opt_sort(tab_hist_t **tab, int fd)
{
    int l_tab = length_tab_hist(tab) - 1;
    for (; l_tab >= 0; l_tab -= 1) {
        dprintf(fd, "%s  %s   %s", tab[l_tab]->num, tab[l_tab]->time,
        tab[l_tab]->command);
    }
    return SUCCESS;
}

int opt_without_info(tab_hist_t **tab, int fd)
{
    for (int i = 0; tab[i] != NULL; i += 1) {
        dprintf(fd, "%s", tab[i]->command);
    }
    return SUCCESS;
}

int display_history(tab_hist_t **tab, int fd, mysh_t *mysh)
{
    char *time = create_time_line();
    char *num = num_to_str(mysh->history.num_command);
    for (int i = 0; tab[i] != NULL; i += 1) {
        dprintf(fd, "%s  %s   %s", tab[i]->num, tab[i]->time, tab[i]->command);
    }
    dprintf(fd, "%s  %s   %s", num, time, "history\n");
    free(time);
    free(num);
    return SUCCESS;
}

int do_history(mysh_t *mysh, command_t to_exec)
{
    if (to_exec.command[1] == NULL) {
        return display_history(mysh->history.tab_hist, to_exec.fd_out, mysh);
    }
    if (strcmp(to_exec.command[1], "-c") == 0)
        return opt_clear(mysh);
    if (strcmp(to_exec.command[1], "-r") == 0)
        return opt_sort(mysh->history.tab_hist, to_exec.fd_out);
    if (strcmp(to_exec.command[1], "-h") == 0)
        return opt_without_info(mysh->history.tab_hist, to_exec.fd_out);
    if (strcmp(to_exec.command[1], "-T") == 0)
        return display_history(mysh->history.tab_hist, to_exec.fd_out, mysh);
    else {
        printf("Usage: history [-chrSLMT] [# number of events].\n");
        mysh->last_status = 1;
    }
    return SUCCESS;
}
