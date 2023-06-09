/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** strcat_dup
*/

#include <stdlib.h>
#include <string.h>

static char *get_new(int len_dest, int len_src, char *dest, char *src)
{
    char *res = malloc(sizeof(char) * (len_dest + len_src + 2));
    int i = 0;

    if (res == NULL)
        return NULL;
    for (int j = 0; j < len_dest + len_src + 2; j += 1)
        res[j] = '\0';
    for (int j = 0; j < len_dest; j += 1){
        res[i] = dest[j];
        i += 1;
    }
    for (int j = 0; j < len_src; j += 1){
        res[i] = src[j];
        i += 1;
    }
    return res;
}

char *my_strcat_dup(char *dest, char *src)
{
    int len_dest = 0;
    int len_src = 0;

    if (dest == NULL)
        return src;
    if (src == NULL)
        return dest;
    len_dest = strlen(dest);
    len_src = strlen(src);
    return get_new(len_dest, len_src, dest, src);
}
