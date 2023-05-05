/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** manage_enter_function
*/

#include "mysh.h"
#include "str_func.h"

void manage_enter_function(mysh_t *mysh)
{
    if (!mysh->completion.display) {
        mysh->enter = true;
        return;
    }
    free_array(mysh->completion.names);
    mysh->completion.display = false;
    printf("\033[0J");
    mysh->completion.index = -1;
}
