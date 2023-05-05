/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** remove_inhibitors
*/

#include <string.h>
#include "parser/ast.h"
#include "macro_errors.h"

int remove_inhibitors(char *command)
{
    int len = strlen(command);
    int context = 0;
    int ind = 0;

    if (len < 0)
        return ERROR;
    for (int i = 0; i < len; i += 1) {
        if (command[i] == '\"' || command[i] == '`' || command[i] == '\'')
            context = context == 0 ? 1 : 0;
        if (context == 0 && command[i] == '\\')
            i += 1;
        command[ind ++] = command[i];
    }
    for (int i = 0; i < len; i += 1)
        command[ind ++] = '\0';
    return SUCCESS;
}
