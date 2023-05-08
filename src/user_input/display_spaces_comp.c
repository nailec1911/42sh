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

void choose_color(mysh_t *mysh)
{
    if (mysh->completion.count > 6)
        mysh->completion.count = 0;
    if (mysh->completion.count == 0)
        mysh->completion.color = 31;
    if (mysh->completion.count == 1)
        mysh->completion.color = 32;
    if (mysh->completion.count == 2)
        mysh->completion.color = 33;
    if (mysh->completion.count == 3)
        mysh->completion.color = 34;
    if (mysh->completion.count == 4)
        mysh->completion.color = 35;
    if (mysh->completion.count == 5)
        mysh->completion.color = 36;
    if (mysh->completion.count == 6)
        mysh->completion.color = 37;
}

void choose_print(int i, mysh_t *mysh)
{
    int spaces = mysh->completion.max_size - strlen(mysh->completion.names[i]);

    if (mysh->completion.index != i)
        printf("\033[0m%s%*s\033[0m",
        mysh->completion.names[i], spaces, " ");
    else {
        choose_color(mysh);
        printf("\033[%d;7m%s%*s\033[0m", mysh->completion.color,
        mysh->completion.names[i], spaces, " ");
        mysh->completion.count += 1;
    }
}

void display_spaces_comp(mysh_t *mysh, int count, int *length)
{
    mysh->completion.nb_lines = 0;
    for (int i = 0; mysh->completion.names[i] != NULL; i += 1) {
        if (count % 3 == 0) {
            printf("\n");
            mysh->completion.length_comp = 0;
            mysh->completion.nb_lines += 1;
        }
        choose_print(i, mysh);
        mysh->completion.length_comp += 1;
        count += 1;
    }
    mysh->completion.length_comp =
    (mysh->completion.length_comp * mysh->completion.max_size) -
    (*length + 2 - mysh->completion.length_word);
}
