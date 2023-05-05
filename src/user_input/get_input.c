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
#include "macros_inputs.h"
void arrow_function(int *index, int *length, char **line, mysh_t *mysh);
void right_arrow_function(int *index, int length);
void left_arrow_function(int *index);
char *ctrl_d_function(mysh_t *mysh);
void manage_enter_function(mysh_t *mysh);
void manage_tab_function(int *length, int *index, char **line, mysh_t *mysh);
void set_terminal(struct termios *o_term, struct termios *term, mysh_t *mysh);
void backward_function(mysh_t *mysh, int *length, int *index, char **line);
char *remove_char(char *line, int index, int length);

static char *fill_string(char *line, mysh_t *mysh, int *index, int *length)
{
    int res = *index;
    int temp = res;
    if (mysh->completion.display) {
        mysh->completion.display = false;
        printf("\033[0J");
        mysh->completion.index = -1;
        free_array(mysh->completion.names);
    }
    memmove(&line[*index + 1], &line[*index], *length - *index);
    line[*index] = mysh->ch;
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

static bool is_inib_odd(int length, char *line)
{
    int count = 0;

    if (line[length] != '\\')
        return false;
    while (line[length] == '\\' && length >= 0) {
        count += 1;
        length -= 1;
    }
    if (count % 2 == 1)
        return true;
    return false;
}

static char *is_inib(char *line)
{
    char *get = NULL;
    size_t len = 0;
    int length = strlen(line) - 2;

    if (strlen(line) == 1 || !is_inib_odd(length, line))
        return line;
    write(STDOUT_FILENO, "? ", 2);
    getline(&get, &len, stdin);
    line[length] = ' ';
    length += 1;
    for (int i = 0; get[i] != '\n' && get[i] != '\0'; i += 1) {
        line[length] = get[i];
        length += 1;
    }
    line[length] = '\n';
    if (line[length - 1] == '\\')
        is_inib(line);
    return line;
}

static char *ch_functions(mysh_t *mysh, int *index, int *length, char *line)
{
    switch (mysh->ch) {
        case ESC:
            arrow_function(index, length, &line, mysh);
            break;
        case CTRL_D:
            return ctrl_d_function(mysh);
        case DELETE:
            backward_function(mysh, length, index, &line);
            break;
        case '\t':
            manage_tab_function(length, index, &line, mysh);
            break;
        case ENTER:
            manage_enter_function(mysh);
            break;
        default:
            line = fill_string(line, mysh, index, length);
    }
    fflush(stdout);
    return line;
}

char *get_input(mysh_t mysh)
{
    struct termios term;
    struct termios o_term;
    int index = 0;
    int length = 0;
    char *line = malloc(sizeof(char) * 1024);

    memset(line, 1024, '0');
    set_terminal(&o_term, &term, &mysh);
    mysh.ch = 0;
    while (read(STDIN_FILENO, &mysh.ch, 1) > 0) {
        if ((line = ch_functions(&mysh, &index, &length, line)) == NULL)
            return NULL;
        if (mysh.tab || mysh.enter)
            break;
    }
    printf("\n");
    line[strlen(line)] = '\n';
    tcsetattr(STDIN_FILENO, TCSANOW, &o_term);
    line = is_inib(line);
    return line;
}
