/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** ctrl_d_function
*/

#include <stdlib.h>
#include "str_func.h"
#include "mysh.h"

char *ctrl_d_function(mysh_t *mysh)
{
    if (mysh->completion.display) {
        printf("\033[0J");
        free_array(mysh->completion.names);
    }
    return NULL;
}
