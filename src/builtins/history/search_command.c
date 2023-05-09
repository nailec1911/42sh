/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <unistd.h>
#include <str_func.h>
#include <stdlib.h>
#include <string.h>
#include "mysh.h"
#include "macro_errors.h"

static char *search_by_num_command(mysh_t *mysh, char *last_input)
{
    int num_command = 0;
    char *command = NULL;
    int to_compare = 0;

    if (!mysh || !last_input || mysh->history.tab_hist == NULL)
        return last_input;
    to_compare = atoi(last_input);
    for (int i = 0; mysh->history.tab_hist[i] != NULL; i += 1) {
        num_command = atoi(mysh->history.tab_hist[i]->num);
        if (num_command == to_compare) {
            command = strdup(mysh->history.tab_hist[i]->command);
            return command;
        }
    }
    return last_input;
}

static char *search_by_name_command(mysh_t *mysh, char *last_input)
{
    char *command = NULL;
    char **tmp = NULL;
    int len = 0;

    if (!mysh || !last_input)
        return last_input;
    len = strlen(last_input);
    for (int i = mysh->history.len_tab_hist - 1; i >= 0; i -= 1) {
        tmp = my_str_to_word_array_separator
        (mysh->history.tab_hist[i]->command, "\n");
        if (tmp == NULL)
            return NULL;
        if (strncmp(last_input, tmp[0], len) == 0) {
            command = my_strcat_dup(tmp[0], "\n");
            free_array(tmp);
            return command;
        }
        free_array(tmp);
    }
    return last_input;
}

char *search_by_type(mysh_t *mysh, char *last_input, int type)
{
    char *to_compare = NULL;

    if (!mysh || !last_input)
        return NULL;
    to_compare = strdup(last_input);
    if (type == 1)
        last_input = search_by_num_command(mysh, last_input);
    else
        last_input = search_by_name_command(mysh, last_input);
    if (last_input && strcmp(last_input, to_compare) != 0) {
        free(to_compare);
        return last_input;
    }
    fprintf(stderr, "%s: Event not found.\n", last_input);
    mysh->last_status = 1;
    free(to_compare);
    return NULL;
}
