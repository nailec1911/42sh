/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <unistd.h>
#include <time.h>
#include "str_func.h"
#include <stdlib.h>
#include "mysh.h"
#include <string.h>

char *remake_command(char **tab)
{
    char *final_input = NULL;
    char *temp = NULL;
    int i = 3;
    if (length_tab(tab) < 3) {
        return strdup(tab[1]);
    }
    final_input = strdup(tab[2]);
    for (; tab[i] != NULL; i += 1) {
        temp = my_strcat_dup(final_input, " ");
        free(final_input);
        final_input = my_strcat_dup(temp, tab[i]);
        free(temp);
    }
    return final_input;
}

char *clean_last_input(char **tab_alias)
{
    char *to_free = NULL;
    char *res = NULL;

    to_free = remake_command(tab_alias);
    res = my_strcat_dup(to_free, "\n");
    free(to_free);
    return res;
}
