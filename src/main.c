/*
** EPITECH PROJECT, 2023
** stumper
** File description:
** main
*/

#include <stddef.h>
#include "macro_errors.h"
int mysh(char * const env[]);

int main(const int argc, char **argv, char * const env[])
{
    (void)argv;

    if (argc != 1 || env == NULL)
        return ERROR;
    return mysh(env);
}
