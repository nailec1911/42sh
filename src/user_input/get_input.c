/*
** EPITECH PROJECT, 2023
** B-PSU-100-BDX-1-1-navy-adam.de-lacheisserie-levy
** File description:
** input
*/

#include <stdio.h>
#include <unistd.h>
#include <termio.h>
#include <string.h>
#include <stdlib.h>
#include "str_func.h"
void arrow_function(int *index, int length);
void right_arrow_function(int *index, int length);
void left_arrow_function(int *index);
void set_terminal(struct termios *old_term, struct termios *term);

static char *remove_char(char *line, int index, int length)
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

static void backward_function(int *length, int *index, char **line)
{
    int res = *index;
    int temp = res;

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

static char *fill_string(char *line, int ch, int *index, int *length)
{
    int res = *index;
    int temp = res;

    memmove(&line[*index + 1], &line[*index], *length - *index + 1);
    line[*index] = ch;
    *index += 1;
    *length += 1;
    for (int i = res; i <= *length; i += 1)
        printf("\033[C");
    for (int k = 0; k <= *length; k += 1)
        printf("\b \b");
    printf("%s", line);
    for (int z = temp; z < *length - 1; z += 1)
        printf("\033[D");
    return line;
}

static char *ch_functions(int ch, int *index, int *length, char *line)
{
    switch (ch) {
        case 27:
            arrow_function(index, *length);
            break;
        case 4:
            return NULL;
        case 127:
            backward_function(length, index, &line);
            break;
        default:
            line = fill_string(line, ch, index, length);
    }
    fflush(stdout);
    return line;
}

char *get_input(void)
{
    struct termios term;
    struct termios old_term;
    int ch = 0;
    int index = 0;
    int length = 0;
    char *line = malloc(sizeof(char) * 1024);
    char *new = NULL;

    for (int i = 0; i < 1024; i += 1)
        line[i] = '\0';
    set_terminal(&old_term, &term);
    while (read(STDIN_FILENO, &ch, 1) > 0 && ch != 10)
        if ((line = ch_functions(ch, &index, &length, line)) == NULL)
            return NULL;
    printf("\n");
    new = my_strcat_dup(line, "\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    free(line);
    return new;
}
