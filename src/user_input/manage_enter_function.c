/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** manage_enter_function
*/

#include "mysh.h"

void manage_enter_function(mysh_t *mysh)
{
    if (!mysh->completion.display) {
        mysh->enter = true;
        return;
    }
    mysh->completion.display = false;
    printf("\033[0J");
    mysh->completion.index = -1;
}
