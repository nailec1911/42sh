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

int display_alias(char **tab_file, int fd)
{
    int l_tab = 0;

    if (!tab_file)
        return SUCCESS;
    l_tab = my_strstrlen(tab_file) - 1;
    for (; l_tab >= 0; l_tab -= 1) {
        dprintf(fd, "%s", tab_file[l_tab]);
    }
    return SUCCESS;
}

static int search_specific_alias(char *line, char *to_find, int fd)
{
    int len = 0;

    if (!to_find || !line)
        return ERROR;
    len = strlen(to_find);
    line += 6;
    if (strncmp(line, to_find, len) == 0) {
        dprintf(fd, "%s", line + len + 1);
        return EXIT;
    }
    return SUCCESS;
}

int display_specific_alias(char **tab_file, char *to_find, int fd)
{
    int l_tab = 0;
    int res = SUCCESS;

    if (!to_find || !tab_file)
        return ERROR;
    l_tab = my_strstrlen(tab_file) - 1;
    for (;l_tab >= 0 && res == SUCCESS; l_tab -= 1) {
        res = search_specific_alias(tab_file[l_tab], to_find, fd);
        if (res == ERROR)
            return ERROR;
    }
    return SUCCESS;
}
