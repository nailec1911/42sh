/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** arrows_func
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "str_func.h"
#include "macros_inputs.h"
#include "input/get_input.h"

int arrow_function(int *index, int *length, char **line, mysh_t *mysh)
{
    if (mysh->completion.display) {
        mysh->completion.display = false;
        printf("\033[0J");
        mysh->completion.index = -1;
        free_array(mysh->completion.names);
    }
    if (read(STDIN_FILENO, &mysh->ch, 1) == -1)
        return EXIT_FAILURE;
    if (mysh->ch == BRACKET) {
        if (read(STDIN_FILENO, &mysh->ch, 1) == -1)
            return EXIT_FAILURE;
        choose_arrow(mysh, index, length, line);
    }
    if (mysh->ch == '3') {
        if (read(STDIN_FILENO, &mysh->ch, 1) == -1)
            return EXIT_FAILURE;
        *line = suppr_function(index, length, *line);
    }
    return EXIT_SUCCESS;
}
