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

char *remove_first_char(char *input)
{
    int idx = 0;
    int to_malloc = strlen(input);
    char *new_input = NULL;
    if ((new_input = malloc(sizeof(char *) * to_malloc)) == NULL)
        return NULL;
    new_input[to_malloc] = '\n';
    for (int i = 1; input[i] != '\n'; i += 1) {
        new_input[idx] = input[i];
        idx += 1;
    }
    return new_input;
}

char *search_by_num_command(mysh_t *mysh, char *last_input)
{
    char **tab_hist = NULL;
    char *to_free = last_input;
    char *to_compare = strdup(last_input);

    for (int i = 0; mysh->history.tab_file[i] != NULL; i += 1) {
        tab_hist = my_str_to_word_array_separator(mysh->history.tab_file[i], " \n");
        if (tab_hist == NULL)
            return NULL;
        free(last_input);
        last_input = remake_command(tab_hist);
        if (strcmp(last_input, to_compare) == 0) {
            free(to_free);
            free(to_compare);
            return last_input;
        }
    }
    free(to_free);
    free(last_input);
    return to_compare;
}

char *search_by_name_command(mysh_t *mysh, char *last_input)
{
    char **tab_hist = NULL;
    char *to_free = last_input;
    char *to_compare = strdup(last_input);

    for (int i = 0; mysh->history.tab_file[i] != NULL; i += 1) {
        tab_hist = my_str_to_word_array_separator
        (mysh->history.tab_file[i], " \n");
        if (tab_hist == NULL)
            return NULL;
        free(last_input);
        last_input = remake_command(tab_hist);
        if (strcmp(tab_hist[0], to_compare) == 0) {
            free(to_free);
            free(to_compare);
            return last_input;
        }
    }
    free(to_free);
    free(last_input);
    return to_compare;
}

char *search_by_name(mysh_t *mysh, char *last_input)
{
    char *to_free = last_input;
    char *to_compare = strdup(last_input);

    if ((last_input = search_by_name_command(mysh, last_input)) == NULL) {
        free(to_compare);
        free(to_free);
        return last_input;
    }
    if (strcmp(last_input, to_compare) != 0) {
        free(to_free);
        free(to_compare);
        return last_input;
    }
    fprintf(stderr, "%s: Event not found.\n", last_input);
    free(to_free);
    free(to_compare);
    return NULL;
}


char *search_by_num(mysh_t *mysh, char *last_input)
{
    char *to_free = last_input;
    char *to_compare = strdup(last_input);

    if ((last_input = search_by_num_command(mysh, last_input)) == NULL) {
        free(to_free);
        free(to_compare);
        return last_input;
    }
    if (strcmp(last_input, to_compare) != 0) {
        free(to_free);
        free(to_compare);
        return last_input;
    }
    fprintf(stderr, "%s: Event not found.\n", last_input);
    free(to_compare);
    free(to_free);
    return NULL;
}

char *do_exclamation_mark(mysh_t *mysh, char *input)
{
    char *last_input = remove_first_char(input);

    if (last_input == NULL)
        return NULL;
    if (input[0] == '!' && input[1] == '\n') {
        mysh->last_status = 1;
        fprintf(stderr, "!: Command not found.\n");
        free(input);
        return "\n";
    }
    if (is_num(last_input) == true) {
        if ((last_input = search_by_num(mysh, last_input)) == NULL)
            return NULL;
        return last_input;
    } else {
        if ((last_input = search_by_name(mysh, last_input)) == NULL)
            return NULL;
        return last_input;
    }
}
