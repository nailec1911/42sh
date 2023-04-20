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

int search_command(mysh_t *mysh, char *input, char **final_input)
{
    char **tab_hist = NULL;
    char *temp = NULL;

    for (int i = 0; mysh->history.tab_file[i] != NULL; i += 1) {
        tab_hist = my_str_to_word_array_separator
        (mysh->history.tab_file[i], " \n");
        *final_input = remake_command(tab_hist);
        temp = my_strcat_dup("!", *final_input);
        if (strcmp(temp, input) == 0) {
            free(temp);
            free_array(tab_hist);
            return SUCCESS;
        }
        free(temp);
        free_array(tab_hist);
    }
    return ERROR;
}

int do_exclamation_mark(mysh_t *mysh, char *input)
{
    char *last_input = NULL;

    if (input[0] == '!' && input[1] == '\n') {
        mysh->last_status = 1;
        fprintf(stderr, "!: Command not found.\n");
        return SUCCESS;
    }
    if (search_command(mysh, input, &last_input) == ERROR) {
        mysh->last_status = 1;
        printf("%s: Event not found.\n", input);
        return SUCCESS;
    }
    return SUCCESS;
}
