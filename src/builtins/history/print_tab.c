/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <unistd.h>
#include <stdio.h>

void print_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i += 1) {
        printf("%s\n", tab[i]);
    }
}
