/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** insert_array_in_array
*/

#include <stdlib.h>
#include "macro_errors.h"
int my_strstrlen(char *str[]);

char **insert_array_in_array(char **to_insert, char **dest, int index)
{
    int len1 = my_strstrlen(to_insert);
    int len2 = my_strstrlen(dest);
    char **res = malloc(sizeof(char *) * (len1 + len2 + 1));
    int ind = 0;

    if (!res)
        return NULL;
    for (int i = 0; ind < index; i += 1)
        res[ind++] = dest[i];
    for (int i = 0; i < len1; i += 1)
        res[ind++] = to_insert[i];
    for (int i = index + 1; i < len2; i += 1)
        res[ind++] = dest[i];
    res[ind] = NULL;
    free(dest);
    return res;
}
