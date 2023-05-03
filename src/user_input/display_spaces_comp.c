/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** display_spaces_comp
*/

#include <unistd.h>
#include <string.h>
#include "mysh.h"

void get_name_max_size(mysh_t *mysh)
{
    int max = strlen(mysh->completion.names[0]);

    for (int i = 1; mysh->completion.names[i] != NULL; i += 1)
        if ((int)strlen(mysh->completion.names[i]) > max)
            max = strlen(mysh->completion.names[i]);
    mysh->completion.max_size = max + 2;
}

void display_spaces_comp(mysh_t *mysh, int count)
{
    int spaces = 0;

    for (int i = 0; mysh->completion.names[i] != NULL; i += 1) {
        if (count % 3 == 0) {
            printf("\n");
        }
        spaces = mysh->completion.max_size - strlen(mysh->completion.names[i]);
        if (mysh->completion.index != i)
            printf("\033[0m%s%*s\033[0m   ",
            mysh->completion.names[i], spaces, " ");
        else
            printf("\033[39;7m%s%*s\033[0m   ",
            mysh->completion.names[i], spaces, " ");
        count += 1;
    }
}
