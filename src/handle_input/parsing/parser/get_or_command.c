/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_or_command
*/

#include <stdlib.h>
#include "parser/create_ast.h"
#include "macro_errors.h"

static int add_elt_in_tab(or_command_t *or_command, and_command_t new_command)
{
    and_command_t * temp = or_command->tab_and_command;

    if ((or_command->tab_and_command =
    malloc(sizeof(and_command_t) * (or_command->nb_and_command+ 1))) == NULL)
        return ERROR;

    for (int i = 0; i < or_command->nb_and_command- 1; i += 1)
        or_command->tab_and_command[i] = temp[i];

    or_command->tab_and_command[or_command->nb_and_command- 1] = new_command;
    or_command->tab_and_command[or_command->nb_and_command].nb_command = -1;
    if (temp != NULL)
        free(temp);
    return SUCCESS;
}

static int fill_tab_command(parser_t *parser, or_command_t *or_command)
{
    or_command->nb_and_command = 1;
    if (add_elt_in_tab(or_command, get_and_command(parser)) == ERROR) {
        parser->error = ERROR;
        return ERROR;
    }
    while (!END_OR_CMD(PEEK(parser)) && parser->error == SUCCESS) {
        parser->cursor += 1;
        or_command->nb_and_command += 1;
        if (add_elt_in_tab(or_command, get_and_command(parser)) == ERROR)
            parser->error = ERROR;
        if (parser->error != 0)
            return parser->error;
        if (END_OR_CMD(PEEK(parser)) == false
        && PEEK(parser).type != OPERATOR_AND) {
            parser->error = FAILURE;
            return parser->error;
        }
    }
    return SUCCESS;
}

or_command_t get_or_command(parser_t *parser)
{
    or_command_t or_command = {0, 0};
    int res = 0;

    or_command.tab_and_command = NULL;
    or_command.nb_and_command = 0;

    if (( res = fill_tab_command(parser, &or_command)) == ERROR){
        parser->error = ERROR;
        return (or_command_t){0, 0};
    }
    return or_command;
}
