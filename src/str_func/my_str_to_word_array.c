/*
** EPITECH PROJECT, 2022
** my_str_to_word_array
** File description:
** ouais
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int count_word(char const *str);

static int my_isalpha(char c)
{
    if (c == ' ' || c == '\t' || c == '\n') {
        return (false);
    }
    return (true);
}

static char *get_word(char *tab, const char *str, int i)
{
    int len = 0;
    int index = i;
    while (my_isalpha(str[i]) == true) {
        len = len + 1;
        i = i + 1;
    }
    tab = malloc(sizeof(char) * (len + 1));
    tab[len] = '\0';
    for (int j = 0; j < len; j = j + 1) {
        tab[j] = str[index];
        index = index + 1;
    }
    return (tab);
}

static int getindex(int index, const char *str)
{
    int nbr = 0;
    int i = 0;
    while (my_isalpha(str[i]) != 1)
        i = i + 1;

    while (str[i] != '\0') {
        if (nbr == index) {
            return (i);
        }
        if (my_isalpha(str[i]) == 0 && my_isalpha(str[i + 1]) == 1) {
            nbr = nbr + 1;
        }
        i = i + 1;
    }
    return (i);
}

char **my_str_to_word_array(char *str)
{
    int index = 0;
    int nbr_mot = count_word(str);
    char **tab = malloc(sizeof(char *) * (nbr_mot + 1));
    int i = 0;

    tab[nbr_mot] = NULL;
    while (i < nbr_mot) {
        index = getindex((i), str);
        tab[i] = get_word(tab[i], str, index);
        i = i + 1;
    }
    return (tab);
}
