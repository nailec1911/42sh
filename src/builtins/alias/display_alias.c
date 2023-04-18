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

int display_alias(mysh_t *mysh)
{
    int l_tab = length_tab(mysh->alias.tab_file) - 1;

    for (; l_tab >= 0; l_tab -= 1) {
        printf("%s", mysh->alias.tab_file[l_tab]);
    }
    return SUCCESS;
}

static int search_specific_alias(mysh_t *mysh, int l_tab, char *to_find)
{
    char *to_display = NULL;
    char **tab_alias = my_str_to_word_array_separator
    (mysh->alias.tab_file[l_tab], " \n");
    if (tab_alias == NULL || tab_alias[2] == NULL)
        return ERROR;
    to_display = remake_command(tab_alias);
    if (to_display == NULL)
        return ERROR;
    if (strcmp(tab_alias[1], to_find) == 0) {
        printf("%s\n", to_display);
        free(to_display);
        free_array(tab_alias);
        return SUCCESS;
    }
    free(to_display);
    free_array(tab_alias);
    return SUCCESS;
}

int display_specific_alias(mysh_t *mysh, char *to_find)
{
    int l_tab = length_tab(mysh->alias.tab_file) - 1;
    for (;l_tab >= 0; l_tab -= 1) {
        return search_specific_alias(mysh, l_tab, to_find);
    }
    return SUCCESS;
}
