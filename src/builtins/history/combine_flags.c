/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include "mysh.h"
#include <string.h>
#include "macro_errors.h"

int compare_char(char **command, int i, history_t *history)
{
    if (command == NULL || history == NULL)
        return ERROR;
    if (command[i][0] != '-')
        return ERROR;
    for (int j = 1; command[i][j] != '\0'; j += 1) {
        if (command[i][j] != 'c' && command[i][j] != 'r'
        && command[i][j] != 'h')
            return ERROR;
        if (command[i][j] == 'c')
            history->flags |= FLAG_C;
        if (command[i][j] == 'r')
            history->flags |= FLAG_R;
        if (command[i][j] == 'h')
            history->flags |= FLAG_H;
    }
    return SUCCESS;

}

int detect_flags(command_t *to_exec, history_t *history)
{
    if (to_exec == NULL || history == NULL)
        return ERROR;
    for (int i = 1; to_exec->args[i] != NULL; i += 1) {
        if (compare_char(to_exec->args, i, history) == ERROR)
            return ERROR;
    }
    return SUCCESS;
}
