/*
** EPITECH PROJECT, 2022
** B-PSU-100-BDX-1-1-sokoban-marius.marolleau
** File description:
** biggest_line
*/
#include <stdio.h>

int biggest_line(char const *str)
{
    int i = 0;
    int count = 0;
    int final_count = 0;
    while (str[i] != '\0') {
        while (str[i] != '\0' && str[i] != '\n') {
            count += 1;
            i += 1;
        }
        if (count > final_count) {
            final_count = count;
        }
        i += 1;
        count = 0;
    }
    return final_count;
}

int next_index(char const *str, int i)
{
    int count = 0;
    while (str[i] != '\n') {
        if (str[i] == '\0') {
            return count;
        }
        i += 1;
        count += 1;
    }
    return count + 1;
}

int nb_char(char const *str, int index)
{
    int i = 0;
    while (str[index] != '\n') {
        if (str[index] == '\0') {
            return (i);
        }
        i += 1;
        index += 1;
    }
    return i;
}

int lenght_map(char **map, int count)
{
    for (int i = 0; map[i] != NULL; i += 1) {
        count += 1;
    }
    return count - 1;

}

int do_width(char *map, int width)
{
    for (int i = 0; map[i] != '\n'; i += 1) {
        width += 1;
    }
    return width -= 2;
}
