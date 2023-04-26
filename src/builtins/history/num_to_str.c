/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <stdlib.h>
#include <stdio.h>

char *num_to_str(int num)
{
    char *str = malloc(sizeof(char) * 7);
    if (str == NULL)
        return NULL;
    str[6] = '\0';
    for (int i = 0; i < 5; i += 1) {
        str[i] = ' ';
    }
    for (int i = 5; i <= 0 || num > 0; i -= 1) {
        str[i] = ((num % 10) + '0');
        num = num / 10;
    }
    return str;
}
