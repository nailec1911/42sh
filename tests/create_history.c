/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include "history.h"
#include "alias.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

tab_hist_t **create_tab_hist(void)
{
    tab_hist_t **tab_hist = malloc(sizeof(tab_hist_t *) * 4);
    tab_hist[0] = malloc(sizeof(tab_hist_t));
    tab_hist[0]->command = strdup("ls\n");
    tab_hist[0]->num = strdup("     1");
    tab_hist[0]->time = strdup("20:00");
    tab_hist[1] = malloc(sizeof(tab_hist_t));
    tab_hist[1]->command = strdup("echo hello\n");
    tab_hist[1]->num = strdup("     2");
    tab_hist[1]->time = strdup("20:50");
    tab_hist[2] = malloc(sizeof(tab_hist_t));
    tab_hist[2]->command = strdup("alias toto ls\n");
    tab_hist[2]->num = strdup("     3");
    tab_hist[2]->time = strdup("01:50");
    tab_hist[3] = malloc(sizeof(tab_hist_t));
    tab_hist[3] = NULL;
    return tab_hist;
}

history_t create_history(void)
{
    history_t hist = {0};
    hist.command = NULL;
    hist.fd_history_file = -1;
    hist.flags = NO_FLAG;
    hist.len_tab_hist = 3;
    hist.num_cmd = 3;
    hist.tab_hist = create_tab_hist();
    return hist;
}
