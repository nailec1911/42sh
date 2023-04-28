/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_and_command
*/

#include <stdlib.h>
#include "parser/token.h"
#include "parser/ast.h"
#include "macro_errors.h"
command_t get_command(parser_t *parser);
bool is_end_command(token_t token);

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
    while (is_end_command(parser->list_tokens[parser->cursor]) == false) {
        parser->cursor += 1;
        and_command->nb_command += 1;
        if (add_elt_in_tab(and_command, get_command(parser)) == ERROR)
            parser->error = ERROR;
        if (parser->error != 0)
            return parser->error;
        if (is_end_command(parser->list_tokens[parser->cursor]) == false
        && parser->list_tokens[parser->cursor].type != PIPE) {
            parser->error = FAILURE;
            return parser->error;
        }
    }
    return SUCCESS;
}

and_command_t get_and_command(parser_t *parser)
{
    and_command_t and_command = {0};
    int res = 0;

    and_command.tab_command = NULL;
    and_command.nb_command = 0;

    if (( res = fill_tab_command(parser, &and_command)) == ERROR){
        parser->error = ERROR;
        return (and_command_t){0};
    }
    return and_command;
}
