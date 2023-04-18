/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include "mysh.h"
#include "history.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char **add_elem_tab(char **tab, char *to_add)
{
    int len_tab = length_tab(tab);
    char **new_tab = NULL;
    if ((new_tab = malloc(sizeof(char *) * (len_tab + 2))) == NULL)
        return NULL;
    new_tab[len_tab + 1] = NULL;
    for (int i = 0; tab[i] != NULL; i += 1) {
        new_tab[i] = strdup(tab[i]);
    }
    new_tab[len_tab] = strdup(to_add);
    return new_tab;
}
