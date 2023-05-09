/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include "history.h"
#include <stdlib.h>
#include <string.h>

history_t create_history()
{
    history_t history = {0};
    history.num_cmd = 3;
    history.fd_history_file = 0;
    history.flags = 0;
    history.len_tab_hist = 4;
    history.tab_hist = calloc(4, sizeof(tab_hist_t *));
    history.tab_hist[0] = malloc(sizeof(tab_hist_t));
    history.tab_hist[0]->command = strdup("ls");
    history.tab_hist[0]->num = strdup("     1");
    history.tab_hist[0]->time = strdup("20:00");
    history.tab_hist[1] = malloc(sizeof(tab_hist_t));
    history.tab_hist[1]->command = strdup("ls -la");
    history.tab_hist[1]->num = strdup("     2");
    history.tab_hist[1]->time = strdup("20:01");
    history.tab_hist[2] = malloc(sizeof(tab_hist_t));
    history.tab_hist[2]->command = strdup("alias toto ls");
    history.tab_hist[2]->num = strdup("     3");
    history.tab_hist[2]->time = strdup("20:04");
    history.tab_hist[3] = NULL;
    return history;
}
