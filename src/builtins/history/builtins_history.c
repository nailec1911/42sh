/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <string.h>
#include <stdlib.h>
#include "mysh.h"
#include "str_func.h"
#include "macro_errors.h"

int opt_clear(mysh_t *mysh)
{
    char **tab = malloc(sizeof(char *) * 2);
    if (tab == NULL)
        return ERROR;
    int l_tab = length_tab(mysh->history->tab_file);
    tab[0] = strdup(mysh->history->tab_file[l_tab - 1]);
    if (tab[0] == NULL)
        return ERROR;
    tab[1] = NULL;
    mysh->history->tab_file = tab;
    return SUCCESS;
}

int opt_sort(mysh_t *mysh)
{
    int l_tab = length_tab(mysh->history->tab_file) - 1;
    for (; l_tab >= 0; l_tab -= 1) {
        printf("%s", mysh->history->tab_file[l_tab]);
    }
    return SUCCESS;
}

int opt_without_info(mysh_t *mysh)
{
    char *to_display = NULL;
    char **tab_cmd = NULL;
    for (int i = 0; mysh->history->tab_file[i] != NULL; i += 1) {
        tab_cmd = my_str_to_word_array_separator
        (mysh->history->tab_file[i], " \n");
        to_display = remake_command(tab_cmd);
        printf("%s\n", to_display);
    }
    return SUCCESS;
}

int display_history(mysh_t *mysh)
{
    for (int i = 0; mysh->history->tab_file[i] != NULL; i += 1) {
        printf("%s", mysh->history->tab_file[i]);
    }
    return SUCCESS;
}

int do_history(mysh_t *mysh, command_t to_exec)
{
    if (to_exec.command[1] == NULL) {
        return display_history(mysh);
    }
    if (strcmp(to_exec.command[1], "-c") == 0)
        return opt_clear(mysh);
    if (strcmp(to_exec.command[1], "-r") == 0)
        return opt_sort(mysh);
    if (strcmp(to_exec.command[1], "-h") == 0)
        return opt_without_info(mysh);
    if (strcmp(to_exec.command[1], "-T") == 0)
        return display_history(mysh);
    else {
        printf("Usage: history [-chrSLMT] [# number of events].\n");
        mysh->last_status = 1;
    }
    return SUCCESS;
}
