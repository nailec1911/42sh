/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** choose_arrow
*/

#include <string.h>
#include "mysh.h"
char *remove_line(int res, int *length, int *index, char *line);
char *parsing_history_spe(char *line, char *str, int *length);
void ctrl_functions(int *index, int *length, int ch);

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

char *up_arrow_function(mysh_t *mysh, int *index, int *length, char *line)
{
    int res = *index;

    if (mysh->history.tab_file == NULL)
        return line;
    if (mysh->ind_history > 0)
        mysh->ind_history -= 1;
    line = parsing_history_spe
    (line, mysh->history.tab_file[mysh->ind_history], length);
    for (int i = res; i <= *length; i += 1)
        printf("\033[C");
    for (int k = 0; k <= *length; k += 1)
        printf("\b \b");
    printf("%s", line);
    *length = strlen(line);
    *index = *length;
    return line;
}

char *down_arrow_function(mysh_t *mysh, int *index, int *length, char *line)
{
    int res = *index;

    mysh->ind_history += 1;
    if (mysh->ind_history == mysh->ind_init)
        return remove_line(res, length, index, line);
    if (mysh->ind_history > length_tab(mysh->history.tab_file) - 1) {
        mysh->ind_history -= 1;
        return line;
    }
    line = parsing_history_spe
    (line, mysh->history.tab_file[mysh->ind_history], length);
    for (int i = res; i <= *length; i += 1)
        printf("\033[C");
    for (int k = 0; k <= *length; k += 1)
        printf("\b \b");
    printf("%s", line);
    *length = strlen(line);
    *index = *length;
    return line;
}

void choose_arrow(mysh_t *mysh, int *index, int *length, char **line)
{
    switch (mysh->ch) {
        case 68:
            left_arrow_function(index);
            break;
        case 67:
            right_arrow_function(index, *length);
            break;
        case 65:
            *line = up_arrow_function(mysh, index, length, *line);
            break;
        case 66:
            *line = down_arrow_function(mysh, index, length, *line);
            break;
        case 49:
            ctrl_functions(index, length, mysh->ch);
    }
}
