/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** change_target_tab
*/

#include <string.h>
#include "str_func.h"
#include "mysh.h"
void display_completion(mysh_t *mysh, char **line, int *length);

static void replace_string(mysh_t *mysh)
{
    for (int j = 0; j < mysh->completion.length_word; j += 1)
        printf("\033[C");
    for (int k = 0; k < mysh->completion.length_word; k += 1)
        printf("\b \b");
    printf("%s", mysh->completion.names[mysh->completion.index]);
}

void change_target_tab(mysh_t *mysh, int *index, int *length, char **line)
{
    if (mysh->completion.index == -1)
        mysh->completion.index = 0;
    else
        mysh->completion.index += 1;
    if (mysh->completion.index == my_strstrlen(mysh->completion.names))
        mysh->completion.index = 0;
    printf("\033[0J");
    display_completion(mysh, line, length);
    for (int i = mysh->completion.ind_space; (*line)[i] != '\0'; i += 1)
        (*line)[i] = '\0';
    replace_string(mysh);
    strcat(*line, mysh->completion.names[mysh->completion.index]);
    *length += strlen(mysh->completion.names[mysh->completion.index])
    - mysh->completion.length_word;
    *index = *length;
}
