/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_and_command
*/

#include <stdlib.h>
#include "parser/create_ast.h"
#include "macro_errors.h"

static int add_elt_in_tab(and_command_t *and_command, command_t new_command)
{
    command_t * temp = and_command->tab_command;

    if ((and_command->tab_command =
    malloc(sizeof(command_t) * (and_command->nb_command + 1))) == NULL)
        return ERROR;

    for (int i = 0; i < and_command->nb_command - 1; i += 1)
        and_command->tab_command[i] = temp[i];

    and_command->tab_command[and_command->nb_command - 1] = new_command;
    and_command->tab_command[and_command->nb_command].nb_command = -1;
    if (temp != NULL)
        free(temp);
    return SUCCESS;
}

static int fill_tab_command(parser_t *parser, and_command_t *and_command)
{
    and_command->nb_command = 1;
    if (add_elt_in_tab(and_command, get_command(parser)) == ERROR) {
        parser->error = ERROR;
        return ERROR;
    }
    while (!END_AND_CMD(parser_peek(parser)) && parser->error == SUCCESS) {
        parser->cursor += 1;
        and_command->nb_command += 1;
        if (add_elt_in_tab(and_command, get_command(parser)) == ERROR)
            parser->error = ERROR;
        if (parser->error != 0)
            return parser->error;
        if (END_AND_CMD(parser_peek(parser)) == false
        && parser_peek(parser).type != PIPE) {
            parser->error = FAILURE;
            return parser->error;
        }
    }
    return SUCCESS;
}

and_command_t get_and_command(parser_t *parser)
{
    and_command_t and_command = {0, 0};
    int res = 0;

    and_command.tab_command = NULL;
    and_command.nb_command = 0;
    if (( res = fill_tab_command(parser, &and_command)) == ERROR){
        parser->error = ERROR;
        return (and_command_t){0, 0};
    }
    return and_command;
}
