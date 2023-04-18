/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <unistd.h>
#include "str_func.h"

char *remake_input(char **tab)
{
    char *final_input = tab[0];
    int i = 1;
    for (; tab[i] != NULL; i += 1) {
        final_input = my_strcat_dup(final_input, " ");
        final_input = my_strcat_dup(final_input, tab[i]);
    }
    final_input = my_strcat_dup(final_input, "\n");
    return final_input;
}
