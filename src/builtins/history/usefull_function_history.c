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
    char *time_str = ctime(&timestamp);
    char **tab_time = my_str_to_word_array_separator(time_str, " ");
    char **hours_tab = my_str_to_word_array_separator(tab_time[3], ":");
    char *time_line = my_strcat_dup(hours_tab[0], ":");
    char *full_time = my_strcat_dup(time_line, hours_tab[1]);
    free_array(tab_time);
    free_array(hours_tab);
    free(time_line);
    return full_time;
}

int length_tab_hist(tab_hist_t **tab)
{
    if (tab == NULL || tab[0] == NULL)
        return 0;
    int len = 0;
    for (int i = 0; tab[i] != NULL; i += 1) {
        len += 1;
    }
    return len;
}

void free_tab_hist(tab_hist_t **tab)
{
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
    if (tab == NULL || tab[0] == NULL)
        return 0;
    int len = 0;
    for (int i = 0; tab[i] != NULL; i += 1) {
        len += 1;
    }
    return len;
}

void print_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i += 1) {
        printf("%s\n", tab[i]);
    }
}
