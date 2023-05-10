/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** is_alias
*/

#include <stdlib.h>
#include <string.h>
#include "alias.h"
#include "str_func.h"

static char *check_is_alias(char **tab_alias, char *input, char *to_search)
{
    char *res = input;

    if (!tab_alias[2])
        return input;
    if (strcmp(to_search, tab_alias[1]) == 0) {
        if ((res = clean_last_input(tab_alias)) == NULL)
            return NULL;
        free(input);
    }
    free_array(tab_alias);
    return res;
}

char *is_alias(alias_t *alias, char *input)
{
    char **tab_alias = NULL;
    char *res = NULL;

    if (!alias || !alias->tab_file || !input)
        return NULL;
    for (int i = 0; alias->tab_file[i] != NULL; i += 1) {
        tab_alias = my_str_to_word_array(alias->tab_file[i], " \t\n");
        if (tab_alias == NULL)
            return NULL;
        res = check_is_alias(tab_alias, res, input);
    }
    return res;
}
