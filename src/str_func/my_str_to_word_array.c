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

int count_word(char const *str, char const *separator);

static int my_is_not_separator(char c, char const *separator)
{
    for (int i = 0; separator[i] != '\0'; i += 1) {
        if (separator[i] == c || c == '\0')
            return false;
    }
    return (true);
}

static char *get_word(char *tab, const char *str, int i, char const *separator)
{
    int len = 0;
    int index = i;

    while (my_is_not_separator(str[i], separator) == true) {
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

static int getindex(int index, const char *str, char const *separator)
{
    int nbr = 0;
    int i = 0;

    while (my_is_not_separator(str[i], separator) != 1)
        i = i + 1;
    while (str[i] != '\0') {
        if (nbr == index) {
            return (i);
        }
        if (my_is_not_separator(str[i], separator) == 0
        && my_is_not_separator(str[i + 1], separator) == 1) {
            nbr = nbr + 1;
        }
        i = i + 1;
    }
    return (i);
}

char **my_str_to_word_array(char *str, char const *separator)
{
    int index = 0;
    int nbr_mot = count_word(str, separator);
    char **tab = malloc(sizeof(char *) * (nbr_mot + 1));
    int i = 0;

    if (!str || !separator || !tab)
        return NULL;
    tab[nbr_mot] = NULL;
    while (i < nbr_mot) {
        index = getindex((i), str, separator);
        tab[i] = get_word(tab[i], str, index, separator);
        i = i + 1;
    }
    return (tab);
}
