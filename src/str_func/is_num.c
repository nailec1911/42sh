/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <stdbool.h>

bool is_num(char *str)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

bool is_num_colon(char *str)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != ':')
            return false;
    }
    return true;
}

bool is_num_space(char *str)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != ' ')
            return false;
    }
    return true;
}
