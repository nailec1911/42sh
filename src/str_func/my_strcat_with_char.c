/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** str_cat_with_char
*/

#include <stdlib.h>
#include <string.h>
char *my_strcat_dup(char *dest, char *src);

char *my_strcat_with_char(char *dest, char const *src, char c)
{
    int i = 0;
    char *res = NULL;

    if (src == NULL)
        return my_strcat_dup(dest, &c);
    if ((res = malloc(sizeof(char) * (strlen(dest) + strlen(src) + 2))) == NULL)
        return NULL;
    for (; dest[i] != '\0'; i += 1)
        res[i] = dest[i];
    res[i] = c;
    i += 1;
    for (int j = 0; src[j] != '\0'; j += 1){
        res[i] = src[j];
        i = i + 1;
    }
    res[i] = '\0';
    return res;
}
