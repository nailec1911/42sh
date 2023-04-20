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
#include <mysh.h>
#include "str_func.h"
void arrow_function(int *index, int *length, char **line, mysh_t *mysh);
void right_arrow_function(int *index, int length);
void left_arrow_function(int *index);
void set_terminal(struct termios *old_term, struct termios *term);
void backward_function(int *length, int *index, char **line);
char *remove_char(char *line, int index, int length);

static char *fill_string(char *line, int ch, int *index, int *length)
{
    int res = *index;
    int temp = res;

    memmove(&line[*index + 1], &line[*index], *length - *index);
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

static char *ch_functions(mysh_t *mysh, int *index, int *length, char *line)
{
    switch (mysh->ch) {
        case 27:
            arrow_function(index, length, &line, mysh);
            break;
        case 4:
            return NULL;
        case 127:
            backward_function(length, index, &line);
            break;
        default:
            line = fill_string(line, mysh->ch, index, length);
    }
    fflush(stdout);
    return line;
}

char *get_input(mysh_t mysh)
{
    struct termios term;
    struct termios old_term;
    int index = 0;
    int length = 0;
    char *line = malloc(sizeof(char) * 1024);
    char *new = NULL;

    for (int i = 0; i < 1024; i += 1)
        line[i] = '\0';
    set_terminal(&old_term, &term);
    while (read(STDIN_FILENO, &mysh.ch, 1) > 0 && mysh.ch != 10)
        if ((line = ch_functions(&mysh, &index, &length, line)) == NULL)
            return NULL;
    printf("\n");
    new = my_strcat_dup(line, "\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    free(line);
    return new;
}
