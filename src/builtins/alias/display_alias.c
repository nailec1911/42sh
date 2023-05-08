/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <stdlib.h>
#include <string.h>
#include "mysh.h"
#include "macro_errors.h"
#include "str_func.h"

int display_alias(alias_t alias, int fd)
{
    int l_tab = 0;

    if (alias.tab_file == NULL)
        return SUCCESS;
    l_tab = length_tab(alias.tab_file) - 1;
    for (; l_tab >= 0; l_tab -= 1) {
        dprintf(fd, "%s", alias.tab_file[l_tab]);
    }
    return SUCCESS;
}

static int search_specific_alias(char *line, char *to_find, int fd)
{
    char *to_display = NULL;
    char **tab_alias = NULL;

    if (tab_alias == NULL || tab_alias[2] == NULL)
        return ERROR;
    tab_alias = my_str_to_word_array_separator(line, " \n");
    if (tab_alias == NULL)
        return ERROR;
    if ((to_display = remake_command(tab_alias)) == NULL)
        return ERROR;
    if (strcmp(tab_alias[1], to_find) == 0) {
        dprintf(fd, "%s\n", to_display);
        free(to_display);
        free_array(tab_alias);
        return EXIT;
    }
    free(to_display);
    free_array(tab_alias);
    return SUCCESS;
}

int display_specific_alias(alias_t alias, char *to_find, int fd)
{
    int l_tab = 0;
    int res = SUCCESS;

    if (to_find == NULL)
        return ERROR;
    l_tab = length_tab(alias.tab_file) - 1;
    for (;l_tab >= 0 && res == SUCCESS; l_tab -= 1) {
        res = search_specific_alias(alias.tab_file[l_tab], to_find, fd);
        if (res == ERROR)
            return ERROR;
    }
    return SUCCESS;
}
