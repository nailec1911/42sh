/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <string.h>
#include <stdlib.h>
#include "mysh.h"
#include "macro_errors.h"
#include "str_func.h"
#include "init.h"

char *search_command(mysh_t *mysh, char *last_input)
{
    if (is_num(last_input)) {
        if ((last_input = search_by_num(mysh, last_input)) == NULL)
            return NULL;
        printf("%s", last_input);
        return last_input;
    } else {
        if ((last_input = search_by_name(mysh, last_input)) == NULL)
            return NULL;
        printf("%s", last_input);
        return last_input;
    }
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
        return NULL;
    }
    return search_command(mysh, last_input);
}
