/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** my_strlen
*/

#include <stddef.h>

int my_strlen(char const *str)
{
    int len = 0;
    if (str == NULL)
        return 0;
    for (; str[len] != '\0'; len += 1);
    return len;
}
