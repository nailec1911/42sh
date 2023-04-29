/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** tab_function
*/

#include <string.h>
#include "mysh.h"

char *manage_tab_function(int *length, int *index, char **line, mysh_t *mysh)
{
    if (*line[0] == '\0') {
        mysh->tab = true;
        return strcpy(*line, "ls");
    }
}