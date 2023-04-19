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
        temp = my_strcat_dup(final_input, " ");
        free(final_input);
        final_input = my_strcat_dup(temp, tab[i]);
        free(temp);
    }
    temp = my_strcat_dup(final_input, "\n");
    free(final_input);
    return temp;
}
