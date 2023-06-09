/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** line_parsing
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "str_func.h"
#include "input/tab_function.h"

static int malloc_parsing(mysh_t *mysh, int ind, char **line, char *mid_line)
{
    mysh->completion.current =
    malloc(sizeof(char) * strlen(&((*line)[ind])) + 1);
    if (mysh->completion.current == NULL)
        return EXIT_FAILURE;
    mysh->completion.current = strcpy(mysh->completion.current, &(*line)[ind]);
    mysh->completion.temp = my_strcat_dup(find_in_env(mysh->env, "PWD="), "/");
    mysh->completion.path = my_strcat_dup(mysh->completion.temp, mid_line);
    free(mid_line);
    free(mysh->completion.temp);
    return EXIT_SUCCESS;
}

int parse_line(mysh_t *mysh, char **line, int *length)
{
    int ind = *length;
    int memo = 0;
    int index = 0;
    char *mid_line = malloc(sizeof(char) * (*length + 1));
    if (mid_line == NULL)
        return EXIT_FAILURE;

    for (; ind > 0 && (*line)[ind - 1] != ' ' &&
    (*line)[ind - 1] != '/'; ind -= 1);
    memo = ind;
    mysh->completion.ind_space = memo;
    for (; memo > 0 && (*line)[memo - 1] != ' '; memo -= 1);
    for (; memo < ind; memo += 1) {
        mid_line[index] = (*line)[memo];
        index += 1;
    }
    mid_line[index] = '\0';
    malloc_parsing(mysh, ind, line, mid_line);
    return EXIT_SUCCESS;
}
