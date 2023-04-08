/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** is_in
*/

#include <stddef.h>

int is_in(char c, char *str)
{
    if (str == NULL)
        return 1;
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == c)
            return 0;
    }
    return 1;
}
