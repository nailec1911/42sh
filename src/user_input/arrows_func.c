/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** arrows_func
*/

#include <unistd.h>
#include <stdio.h>
char *suppr_function(int *index, int *length, char *line);

static void left_arrow_function(int *index)
{
    if (*index > 0) {
        *index -= 1;
        printf("\033[D");
    }
}

static void right_arrow_function(int *index, int length)
{
    if (*index != length) {
        *index += 1;
        printf("\033[C");
    }
}

void arrow_function(int *index, int *length, char **line)
{
    int ch = 0;

    read(STDIN_FILENO, &ch, 1);
    if (ch == 91) {
        read(STDIN_FILENO, &ch, 1);
        switch (ch) {
            case 68:
                left_arrow_function(index);
                break;
            case 67:
                right_arrow_function(index, *length);
        }
    }
    if (ch == 51) {
        read(STDIN_FILENO, &ch, 1);
        *line = suppr_function(index, length, *line);
    }
}
