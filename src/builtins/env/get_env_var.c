/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** get_env_var
*/

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "macro_errors.h"
#include "mysh.h"
#include "str_func.h"

char *get_env_var(mysh_t *mysh, char *var)
{
    int len_var = strlen(var);

    if (!mysh || !var || !mysh->env)
        return NULL;
    for (int i = 0; mysh->env[i] != NULL; ++i)
        if (strncmp(var, mysh->env[i], len_var) == SUCCESS)
            return mysh->env[i] + len_var;
    return NULL;
}
