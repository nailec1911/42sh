/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "mysh.h"
#include "str_func.h"
#include "history.h"
#include "macro_errors.h"

char *create_time_line(void)
{
    time_t timestamp = time(NULL);
    char **tab_time = NULL;
    char *command = NULL;
    char *time_str = ctime(&timestamp);

    if (time_str == NULL)
        return NULL;
    tab_time = my_str_to_word_array_separator(time_str, " ");
    if (tab_time == NULL)
        return NULL;
    tab_time[3][5] = '\0';
    if ((command = strdup(tab_time[3])) == NULL)
        return NULL;
    free_array(tab_time);
    return command;
}

int length_tab_hist(tab_hist_t **tab)
{
    int len = 0;

    if (tab == NULL || tab[0] == NULL)
        return 0;
    for (int i = 0; tab[i]; i += 1) {
        len += 1;
    }
    return len;
}

void free_tab_hist(tab_hist_t **tab)
{
    if (!tab || !tab[0])
        return;
    for (int i = 0; tab[i] != NULL; i += 1) {
        free(tab[i]->command);
        free(tab[i]->time);
        free(tab[i]->num);
        free(tab[i]);
    }
    free(tab);
}

int length_tab(char **tab)
{
    int len = 0;

    if (tab == NULL || tab[0] == NULL)
        return 0;
    for (int i = 0; tab[i] != NULL; i += 1) {
        len += 1;
    }
    return len;
}

void write_in_file(tab_hist_t **tab, int fd, bool have_file)
{
    if (have_file == false || !tab)
        return;
    for (int i = 0; tab[i] != NULL; i += 1) {
        dprintf(fd, "%s  %s   %s", tab[i]->num, tab[i]->time, tab[i]->command);
    }
}
