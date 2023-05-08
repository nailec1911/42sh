/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exclamation_mark
*/

#include <stdlib.h>
#include <string.h>
#include "mysh.h"
#include "str_func.h"
#include "macro_errors.h"
char *do_exclamation_mark(mysh_t *mysh, char *input);

static char *insert_str(char *src, char *to_insert, int start, int end)
{
    int len = strlen(src) + strlen(to_insert) + 1;
    char *res = calloc(len, 1);
    int ind = 0;

    if (res == NULL)
        return NULL;
    for (int i = 0; i < start; ++ i)
        res[ind ++] = src[i];
    for (int i = 0; to_insert[i]; ++ i)
        res[ind ++] = to_insert[i];
    for (int i = start + end; src[i]; ++ i)
        res[ind ++] = src[i];
    res[ind] = '\0';
    free(src);
    return res;
}

static char *get_new_str_value(mysh_t *mysh, char *str, int from, int to)
{
    char *name = calloc(to + 1, 0);
    char *new = NULL;

    if (name == NULL)
        return str;
    for (int i = 0; i < to; i += 1)
        name[i] = str[from + i];
    new = do_exclamation_mark(mysh, name);
    free(name);
    if (new == NULL)
        return str;
    new[strlen(new) - 1] = '\0';
    return insert_str(str, new, from, to);
}

static char *get_index_change(mysh_t *mysh, char *str, int *i)
{
    int len = 0;

    if (str[*i] == '\\') {
        *i += 1;
        return str;
    }
    if (str[*i] == '!') {
        while (is_in(str[*i + len], " \t\n$|&{};()><") != 0
        && str[*i + len] != '\0')
            len += 1;
        mysh->display_line = true;
        return get_new_str_value(mysh, str, *i, len);
    }
    return str;
}

char *replace_exclamation_mark(mysh_t *mysh, char *input)
{
    for (int i = 0; input[i] != '\0' && input[i + 1] != '\0'
    && mysh->last_status == SUCCESS; i += 1) {
        input = get_index_change(mysh, input, &i);
    }
    return input;
}
