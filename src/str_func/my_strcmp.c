/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** my_strcmp
*/

#include <stddef.h>

static int diff_null(char const *str)
{
    if (str == NULL)
        return 0;
    return str[0];
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;
    int r;

    if (s1 == NULL)
        return diff_null(s2);
    if (s2 == NULL)
        return diff_null(s1);
    while (s1[i] != '\0'){
        r = s1[i] - s2[i];
        if (r != 0){
            return r;
        }
        i = i + 1;
    }
    r = s1[i] - s2[i];
    if (r != 0)
        return r;
    return r;
}
