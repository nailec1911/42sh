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

int count_line(char *str)
{
    int line = 0;

    if (!str)
        return -1;
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == '\n')
            line += 1;
    }
    free(str);
    return line;
}

char *remake_command(char **tab)
{
    char *final_input = NULL;
    char *temp = NULL;
    int i = 3;

    if (!tab)
        return NULL;
    if (length_tab(tab) < 3) {
        return strdup(tab[1]);
    }
    final_input = strdup(tab[2]);
    for (; tab[i] != NULL; i += 1) {
        if ((temp = my_strcat_dup(final_input, " ")) == NULL)
            return NULL;
        free(final_input);
        if ((final_input = my_strcat_dup(temp, tab[i])) == NULL)
            return NULL;
        free(temp);
    }
    return final_input;
}

char *clean_last_input(char **tab_alias)
{
    char *to_free = NULL;
    char *res = NULL;

    if (!tab_alias)
        return NULL;
    if ((to_free = remake_command(tab_alias)) == NULL)
        return NULL;
    if ((res = my_strcat_dup(to_free, "\n")) == NULL)
        return NULL;
    free(to_free);
    return res;
}
