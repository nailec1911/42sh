/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** fd_to_tab
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "str_func.h"
#include "macro_errors.h"

static char *get_file_str(FILE *file)
{
    size_t len = 0;
    char *result = NULL;

    if (!file)
        return NULL;
    if (getdelim(&result, &len, '\0', file) < 0)
        return NULL;
    return result;
}

char **file_stream_to_tab(FILE *file)
{
    char *file_str = get_file_str(file);
    char **tab = NULL;

    if (!file)
        return NULL;
    fclose(file);
    if (file_str == NULL)
        return NULL;
    tab = my_str_to_word_array(file_str, " \t\n");
    free(file_str);
    return tab;
}
