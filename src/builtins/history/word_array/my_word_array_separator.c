/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int nbr_word_separator(char *str, char *separator);
int loop_separator(char c, char *separator);
int find_index_separator(char *str, int idx_pcd, char *separator);
int my_strlen_index_separator(char *str, int index, char *separator);

int where_is_start(char *separator, char *str)
{
    int index = 0;
    if (loop_separator(str[0], separator) == 1) {
        index = 0;
    } else {
        index = find_index_separator(str,0, separator);
    }
    return index;
}

char **my_str_to_word_array_separator(char *str, char *separator)
{
    int nb_word = nbr_word_separator(str, separator);
    int index_str = 0;
    char **tab = malloc(sizeof(char *) * (nb_word + 1));
    int index = where_is_start(separator, str);
    int len_word = 0;

    for (int i = 0; i < nb_word; i += 1) {
        len_word = my_strlen_index_separator(str, index, separator);
        index_str = index;
        tab[i] = malloc(sizeof(char) * (len_word + 1));
        for (int j = 0; j < len_word; j += 1) {
            tab[i][j] = str[index_str];
            index_str += 1;
        }
        tab[i][len_word] = '\0';
        index = find_index_separator(str, index + 1, separator);
    }
    tab[nb_word] = NULL;
    return tab;
}
