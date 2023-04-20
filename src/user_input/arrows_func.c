/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** arrows_func
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "mysh.h"
#include "str_func.h"
char *suppr_function(int *index, int *length, char *line);
void choose_arrow(mysh_t *mysh, int *index, int *length, char **line);

void arrow_function(int *index, int *length, char **line, mysh_t *mysh)
{
    read(STDIN_FILENO, &mysh->ch, 1);
    if (mysh->ch == 91) {
        read(STDIN_FILENO, &mysh->ch, 1);
        choose_arrow(mysh, index, length, line);
    }
    if (mysh->ch == 51) {
        read(STDIN_FILENO, &mysh->ch, 1);
        *line = suppr_function(index, length, *line);
    }
}
