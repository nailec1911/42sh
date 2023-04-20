/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "mysh.h"
#include "alias.h"
#include "str_func.h"
#include "macro_errors.h"
#include "init.h"

static int add_alias_rc(mysh_t *mysh, char *input)
{
    int l_tab = 0;

    if (mysh->alias.tab_file == NULL) {
        mysh->alias.tab_file = malloc(sizeof(char *) * 2);
        if (mysh->alias.tab_file == NULL)
            return ERROR;
        mysh->alias.tab_file[0] = input;
        mysh->alias.tab_file[1] = NULL;
        fprintf(mysh->alias.fd_file, "%s", mysh->alias.tab_file[0]);
    } else {
        if (add_elem_tab_alias(&mysh->alias, input) == ERROR)
            return ERROR;
        l_tab = length_tab(mysh->alias.tab_file);
        fprintf(mysh->alias.fd_file, "%s", mysh->alias.tab_file[l_tab - 1]);
    }
    fflush(mysh->alias.fd_file);
    return SUCCESS;
}

int do_alias(mysh_t *mysh, command_t to_exec)
{
    char *command = NULL;
    if (to_exec.command[1] == NULL) {
        if (mysh->alias.tab_file == NULL)
            return SUCCESS;
        return display_alias(mysh);
    }
    if (to_exec.command[2] == NULL) {
        if (mysh->alias.tab_file == NULL)
            return SUCCESS;
        return display_specific_alias(mysh, to_exec.command[1]);
    } else {
        command = remake_input(to_exec.command);
        if (add_alias_rc(mysh, command) == ERROR) {
            mysh->last_status = 1;
            return ERROR;
        }
    }
    return SUCCESS;
}

static char *check_is_alias(char **tab_alias, char **input, char *to_search)
{
    char *last_input = NULL;
    char *to_compare = my_strcat_dup(tab_alias[1], "\n");
    char *to_free = *input;

    if (tab_alias[2] == NULL)
        return *input;
    if (to_compare == NULL)
        return NULL;
    if (strcmp(to_search, to_compare) == 0) {
        if ((last_input = clean_last_input(tab_alias)) == NULL)
            return NULL;
        *input = last_input;
        free(to_free);
    }
    free_array(tab_alias);
    free(to_compare);
    return *input;
}

char *is_alias(mysh_t *mysh, char *input)
{
    char **tab_alias = NULL;
    char *to_search = my_strcat_dup(input, "\n");

    if (to_search == NULL)
        return NULL;
    if (mysh->alias.tab_file == NULL) {
        free(to_search);
        return input;
    }
    for (int i = 0; mysh->alias.tab_file[i] != NULL; i += 1) {
        tab_alias = my_str_to_word_array_separator
        (mysh->alias.tab_file[i], " \n");
        if (tab_alias == NULL)
            return NULL;
        if ((input = check_is_alias(tab_alias, &input, to_search)) == NULL)
            return NULL;
    }
    free(to_search);
    return input;
}
