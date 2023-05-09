/*
** EPITECH PROJECT, 2023
** strstrlen
** File description:
** oui
*/

#include <stdlib.h>

int my_strstrlen(char *const str[])
{
    int len = 0;
    if (!str)
        return 0;
    while (str[++len]);
    return len;
}
