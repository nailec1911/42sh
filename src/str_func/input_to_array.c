/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** input_to_array
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static bool is_separator(char c, char *separator)
{
    for (int i = 0; separator[i] != '\0'; i += 1) {
        if (separator[i] == c)
            return true;
    }
    return false;
}

static char *word(const char *str, int n, int len, char *separator)
{
    char *temp;
    int i = 0;

    if ((temp = malloc(sizeof(char) * len + 1)) == NULL)
        return NULL;
    for (int j = 0; j < len + 1; j += 1)
        temp[j] = '\0';
    while (!is_separator(str[n], separator)
    && str[n] != '\n' && str[n] != '\0'){
        temp[i] = str[n];
        i = i + 1;
        n = n + 1;
    }
    return temp;
}

static int len_malloc(const char *str, char *separator)
{
    int i = 0;
    int c = 1;

    while (str[i] != '\n' && str[i] != '\0'){
        if (is_separator(str[i], separator)
        && !is_separator(str[i + 1], separator)){
            c = c + 1;
        }
        i = i + 1;
    }
    return c;
}

char **input_to_array(char const *str, char *separator)
{
    char **arr;
    size_t i = 0;
    size_t n = 0;
    size_t j = 0;

    arr = malloc(sizeof(char *) * (len_malloc(str, separator) + 1));
    while (i < strlen(str)){
        n = i;
        while (!is_separator(str[n], separator)
        && str[n] != '\n' && str[n] != '\0')
            n = n + 1;
        if (n != i){
            arr[j] = word(str, i, n - i, separator);
            j = j + 1;
        }
        i = n + 1;
    }
    arr[j] = NULL;
    return arr;
}
