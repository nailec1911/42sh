/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set_magic_quote
*/

#include <string.h>
#include <stdlib.h>
#include "macro_errors.h"
#include "mysh.h"
#include "str_func.h"
#include "magic_quote.h"

static int set_new_params(mysh_t *mysh, command_t *command, int to_mod)
{
    FILE *res_cmd = get_file_res_command(mysh, command->args[to_mod]);
    char **res_array = NULL;

    if (res_cmd == NULL)
        return ERROR;
    res_array = file_stream_to_tab(res_cmd);
    command->args = insert_array_in_array(res_array, command->args, to_mod);
    free(res_array);
    return SUCCESS;
}

static int set_magic_command(mysh_t *mysh, command_t *command)
{
    int res = SUCCESS;

    for (int i = 0; i < command->nb_command; i += 1) {
        if (command->args[i][strlen(command->args[i]) - 1] == MAGIC)
            res = set_new_params(mysh, command, i);
        if (res != SUCCESS)
            return res;
    }
    return SUCCESS;
}

int set_magic_quote(mysh_t *mysh, and_command_t *actual)
{
    if (!mysh || !actual)
        return ERROR;
    for (int i = actual->nb_command - 1; i >= 0; i -= 1) {
        if (set_magic_command(mysh, &(actual->tab_command[i])) == ERROR)
            return ERROR;
    }
    return SUCCESS;
}
