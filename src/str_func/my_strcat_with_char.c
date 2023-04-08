/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** str_cat_with_char
*/

#include <stdlib.h>
int my_strlen(char const *str);

char *my_strcat_with_char(char *dest, char const *src, char c)
{
    int i = 0;
    char *res = malloc(sizeof(char) * (my_strlen(dest) + my_strlen(src) + 2));

    if (res == NULL)
        return NULL;
    for (; dest[i] != '\0'; i += 1)
        res[i] = dest[i];
    res[i] = c;
    i += 1;
    res[i] = '\0';
    if (src == NULL)
        return res;
    for (int j = 0; src[j] != '\0'; j += 1){
        res[i] = src[j];
        i = i + 1;
    }
    res[i] = '\0';
    return res;
}
