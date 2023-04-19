/*
** EPITECH PROJECT, 2022
** B-PSU-100-BDX-1-1-sokoban-marius.marolleau
** File description:
** info_tab
*/
#include <stddef.h>

int get_line(char const *file)
{
    int ligne = 0;
    for (int i = 0; file[i] != '\0'; i += 1) {
        if (file[i] == '\n') {
            ligne += 1;
        }
    }
    return ligne + 1;
}

int get_col(char const *file)
{
    int col = 0;
    for (int i = 0; file[i] != '\n'; i += 1) {
        col += 1;
    }
    return col;
}

char **compare_char(char **map, int i, int j, int *count)
{
    if (map[i][j] == '.') {
        map[i][j] = 'x';
        *count += 1;
        return map;
    } else {
        return map;
    }
}

char **single_line(char **map)
{
    int count = 0;
    for (int i = 0; map[i] != NULL && !count; i += 1) {
        for (int j = 0; map[i][j] != '\0' && !count; j += 1) {
            map = compare_char(map, i, j, &count);
        }
    }
    if (!count) {
        return map;
    } else {
        return map;
    }
}
