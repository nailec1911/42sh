/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** recreate_args
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char **recreate_args(char **args)
{
    char **new_args = calloc(1, sizeof(char*));
    int idx = 0, new_idx = 0;

    if (!new_args)
        return 0;
    for (; args[idx] != 0; new_idx++) {
        char *next_arg = args[idx + 1];
        if (next_arg && next_arg[0] == '=' && next_arg[1] == 0) {
            int buf_len = strlen(args[idx]) + 1 + 1;
            buf_len += next_arg && args[idx + 2] ? strlen(args[idx + 2]) : 0;
            new_args[new_idx] = calloc(buf_len, sizeof(char));
            sprintf(new_args[new_idx], "%s%s%s", args[idx], next_arg,
                    next_arg && args[idx + 2] ? args[idx + 2] : "");
            idx += next_arg && args[idx + 2] ? 3 : 2;
        } else
            new_args[new_idx] = strdup(args[idx++]);
        new_args = realloc(new_args, sizeof(char*) * (new_idx + 2));
    }
    new_args[new_idx] = 0;
    return new_args;
}
