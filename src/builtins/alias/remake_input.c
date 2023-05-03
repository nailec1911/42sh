/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "str_func.h"

char *remake_input(char **tab)
{
    char *final_input = strdup(tab[0]);
    char *temp = NULL;
    int i = 1;
    for (; tab[i] != NULL; i += 1) {
        if ((temp = my_strcat_dup(final_input, " ")) == NULL)
            return NULL;
        free(final_input);
        if ((final_input = my_strcat_dup(temp, tab[i])) == NULL)
            return NULL;
        free(temp);
    }
    if ((temp = my_strcat_dup(final_input, "\n")) == NULL)
        return NULL;
    free(final_input);
    return temp;
}
