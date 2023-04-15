/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** free_env
*/

#include <stdlib.h>
#include "mysh.h"

void free_env(mysh_t *mysh)
{
    if (mysh == NULL)
        return;

    for (int i = 0; mysh->env[i]; ++i)
        free(mysh->env[i]);
}
