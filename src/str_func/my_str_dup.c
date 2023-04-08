/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** str_dup
*/

#include <stdlib.h>
int my_strlen(char const *str);

char *my_str_dup(char const *src)
{
    char *res = 0;
    int i = 0;
    int len = my_strlen(src);

    if (src == NULL)
        return NULL;
    res = malloc(sizeof (char) * (len + 1));
    if (res == NULL)
        return NULL;
    while (src[i] != '\0'){
        res[i] = src[i];
        i = i + 1;
    }
    res[i] = '\0';
    return res;
}
