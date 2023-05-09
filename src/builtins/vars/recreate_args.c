/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** recreate_args
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int count_buf_len(char **args, int idx)
{
    int buf_len = strlen(args[idx]) + 1 + 1;
    buf_len += args[idx + 1] && args[idx + 2] ? strlen(args[idx + 2]) : 0;
    return buf_len;
}

static void append_vars(char **args, char **new_args, int new_idx, int idx)
{
    if (!new_args[new_idx])
        return;
    sprintf(new_args[new_idx], "%s%s%s", args[idx], args[idx + 1],
                    args[idx + 1] && args[idx + 2] ? args[idx + 2] : "");
}

char **recreate_args(char **args)
{
    char **new_args = calloc(1, sizeof(char*));
    int idx = 0;
    int new_idx = 0;

    for (; args && args[idx] != 0; new_idx++) {
        if (!new_args)
            return 0;
        if (args[idx + 1] && args[idx + 1][0] == '=' && args[idx + 1][1] == 0) {
            new_args[new_idx] = calloc(count_buf_len(args, idx), sizeof(char));
            append_vars(args, new_args, new_idx, idx);
            idx += args[idx + 1] && args[idx + 2] ? 3 : 2;
        } else
            new_args[new_idx] = strdup(args[idx++]);
        if (!new_args[new_idx])
            return 0;
        new_args = realloc(new_args, sizeof(char*) * (new_idx + 2));
    }
    new_args[new_idx] = 0;
    return new_args;
}
