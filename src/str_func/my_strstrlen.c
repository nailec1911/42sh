/*
** EPITECH PROJECT, 2023
** strstrlen
** File description:
** oui
*/

#include <stdlib.h>

int my_strstrlen(char *str[])
{
    int len = 0;
    for (; str[len]; ++len);
    return len;
}
