/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** remove_functions
*/

#include <stdio.h>
#include <string.h>
#include "mysh.h"

char *remove_line(int res, int *length, int *index, char *line)
{
    for (int i = res; i <= *length; i += 1)
        printf("\033[C");
    for (int k = 0; k <= *length; k += 1)
        printf("\b \b");
    *length = 0;
    *index = 0;
    for (int j = 0; line[j] != '\0'; j += 1)
        line[j] = '\0';
    return line;
}

char *remove_char(char *line, int index, int length)
{
    int i = index;

    line[index - 1] = '\0';
    if (line[index] == '\0')
        return line;
    for (; i < length; i += 1)
        line[i - 1] = line[i];
    line[i - 1] = '\0';
    return line;
}

void backward_function(mysh_t *mysh, int *length, int *index, char **line)
{
    int res = *index;
    int temp = res;

    if (mysh->completion.display) {
        mysh->completion.display = false;
        printf("\033[0J");
        mysh->completion.index = -1;
    }
    if (*index != 0) {
        *line = remove_char(*line, *index, *length);
        *length -= 1;
        *index -= 1;
        for (int i = res; i <= *length; i += 1)
            printf("\033[C");
        for (int k = 0; k <= *length; k += 1)
            printf("\b \b");
        printf("%s", *line);
        for (int z = temp; z <= *length; z += 1)
            printf("\033[D");
    }
}

char *suppr_function(int *index, int *length, char *line)
{
    int res = *index;
    int temp = res;

    if (*index != *length) {
        line[*index] = '\0';
        memmove(&line[*index], &line[*index + 1], *length - *index);
        *length -= 1;
        for (int i = res; i <= *length; i += 1)
            printf("\033[C");
        for (int k = 0; k <= *length; k += 1)
            printf("\b \b");
        printf("%s", line);
        for (int z = temp; z < *length; z += 1)
            printf("\033[D");
    }
    return line;
}
