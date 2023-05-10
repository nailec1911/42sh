/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <stdbool.h>

bool is_num_char(char *str, char c)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != c)
            return false;
    }
    return true;
}
