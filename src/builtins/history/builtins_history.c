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
#include "history.h"

static tab_hist_t **set_new_history(mysh_t *mysh, int ind_last)
{
    tab_hist_t **tab = malloc(sizeof(tab_hist_t *) * 2);

    if (!mysh || !tab)
        return NULL;
    tab[0] = malloc(sizeof(tab_hist_t));
    if (!tab[0])
        return NULL;
    tab[0]->num = strdup(mysh->history.tab_hist[ind_last - 1]->num);
    tab[0]->time = strdup(mysh->history.tab_hist[ind_last - 1]->time);
    tab[0]->command = strdup(mysh->history.tab_hist[ind_last - 1]->command);
    tab[1] = NULL;
    if (!tab[0]->command || !tab[0]->num || !tab[0]->time)
        return NULL;
    return tab;
}

static int opt_clear(mysh_t *mysh)
{
    tab_hist_t **to_free = NULL;
    int l_tab = 0;

    if (!mysh)
        return ERROR;
    to_free = mysh->history.tab_hist;;
    l_tab = mysh->history.len_tab_hist;
    mysh->history.len_tab_hist = 1;
    mysh->history.tab_hist = set_new_history(mysh, l_tab);
    if (!mysh->history.tab_hist)
        return ERROR;
    free_tab_hist(to_free);
    return SUCCESS;
}

int do_history(mysh_t *mysh, command_t to_exec)
{
    if (!mysh)
        return ERROR;
    if (to_exec.args[1] == NULL) {
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

