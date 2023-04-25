/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include "str_func.h"

char *remove_first_char(char *input)
{
    int idx = 0;
    int to_malloc = my_strlen(input);
    char *new_input = NULL;

    if ((new_input = malloc(sizeof(char) * to_malloc)) == NULL)
        return NULL;
    new_input[to_malloc - 1] = '\0';
    for (int i = 1; input[i] != '\n' && input[i] != '\0'; i += 1) {
        new_input[idx] = input[i];
        idx += 1;
    }
    return new_input;
}
