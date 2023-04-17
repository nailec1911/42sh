/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set_magic_quote
*/

#include "macro_errors.h"
#include "mysh.h"
#include "str_func.h"
#include "magic_quote.h"

static int set_new_params(mysh_t *mysh, command_t *command, int to_mod)
{
    FILE *res_cmd = get_file_res_command(mysh, command->command[to_mod]);

    if (res_cmd == NULL)
        return ERROR;

    if (set_new_tab(command, res_cmd, to_mod) == ERROR)
        return ERROR;
    return SUCCESS;
}

static int set_magic_command(mysh_t *mysh, command_t *command)
{
    int res = SUCCESS;

    for (int i = 0; i < command->nb_command; i += 1) {
        if (command->command[i][my_strlen(command->command[i]) - 1] == '`')
            res = set_new_params(mysh, command, i);
        if (res != SUCCESS)
            return res;
    }
    return SUCCESS;
}

int set_magic_quote(mysh_t *mysh, and_command_t *actual)
{
    for (int i = 0; i < actual->nb_command; i += 1) {
        if (set_magic_command(mysh, &(actual->tab_command[i])) == ERROR)
            return ERROR;
    }
    return SUCCESS;
}
