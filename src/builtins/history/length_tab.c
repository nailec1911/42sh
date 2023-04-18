/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <unistd.h>

int length_tab(char **tab)
{
    int len = 0;
    for (int i = 0; tab[i] != NULL; i += 1) {
        len += 1;
    }
    return len;
}
