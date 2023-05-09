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


static char *search_command(mysh_t *mysh, char *last_input)
{
    char *replace = NULL;

    if (!mysh || !last_input)
        return NULL;
    if (is_num(last_input)) {
        replace = search_by_type(mysh, last_input, 1);
    } else {
        replace = search_by_type(mysh, last_input, 2);
    }
    if (!replace) {
        mysh->last_status = 1;
        mysh->display_line = false;
    }
    free(last_input);
    return replace;
}

char *do_exclamation_mark(mysh_t *mysh, char *input)
{
    char *last_input = NULL;

    if (!mysh || !input)
        return NULL;
    last_input = remove_first_char(input);
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
