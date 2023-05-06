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

char *search_by_num_command(mysh_t *mysh, char *last_input)
{
    int num_command = 0;
    int to_compare = 0;
    char *command = NULL;

    if (mysh == NULL || last_input == NULL)
        return NULL;
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

char *search_by_name_command(mysh_t *mysh, char *last_input)
{
    char *command = NULL;
    char **tmp = NULL;
    int len = strlen(last_input);
    int len_tab_hist = mysh->history.len_tab_hist;

    for (int i = len_tab_hist - 1; i >= 0; i -= 1) {
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

char *search_by_name(mysh_t *mysh, char *last_input)
{
    char *to_compare = NULL;

    if (mysh == NULL || last_input == NULL)
        return NULL;
    to_compare = strdup(last_input);
    if ((last_input = search_by_name_command(mysh, last_input)) == NULL) {
        free(to_compare);
        return last_input;
    }
    if (strcmp(last_input, to_compare) != 0) {
        free(to_compare);
        return last_input;
    }
    fprintf(stderr, "%s: Event not found.\n", last_input);
    free(to_compare);
    return NULL;
}

char *search_by_num(mysh_t *mysh, char *last_input)
{
    char *to_compare = NULL;

    if (mysh == NULL || last_input == NULL)
        return NULL;
    to_compare = strdup(last_input);
    if ((last_input = search_by_num_command(mysh, last_input)) == NULL) {
        free(to_compare);
        return last_input;
    }
    if (strcmp(last_input, to_compare) != 0) {
        free(to_compare);
        return last_input;
    }
    fprintf(stderr, "%s: Event not found.\n", last_input);
    free(to_compare);
    return NULL;
}
