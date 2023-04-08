/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** get_grocommand
*/

#include <stdlib.h>
#include "parser/token.h"
#include "parser/ast.h"
#include "macro_errors.h"
command_t get_command(parser_t *parser);

static int add_elt_in_tab(grocommand_t *grocommand, command_t new_command)
{
    command_t * temp = grocommand->tab_command;

    if ((grocommand->tab_command =
    malloc(sizeof(command_t) * grocommand->nb_command)) == NULL)
        return ERROR;

    for (int i = 0; i < grocommand->nb_command - 1; i += 1)
        grocommand->tab_command[i] = temp[i];

    grocommand->tab_command[grocommand->nb_command - 1] = new_command;

    if (temp != NULL)
        free(temp);
    return SUCCESS;
}

static int fill_tab_command(parser_t *parser, grocommand_t *grocommand)
{
    grocommand->nb_command = 1;
    if (add_elt_in_tab(grocommand, get_command(parser)) == ERROR) {
        parser->error = ERROR;
        return ERROR;
    }
    while (parser->list_tokens[parser->cursor].type != END_LINE
    && parser->list_tokens[parser->cursor].type != SEMICOLON) {
        parser->cursor += 1;
        grocommand->nb_command += 1;
        if (add_elt_in_tab(grocommand, get_command(parser)) == ERROR) {
            parser->error = ERROR;
            return ERROR;
        }
        if (parser->list_tokens[parser->cursor].type != END_LINE
        && parser->list_tokens[parser->cursor].type != PIPE
        && parser->list_tokens[parser->cursor].type != SEMICOLON) {
            return EXIT;
        }
    }
    return SUCCESS;
}

grocommand_t get_grocommand(parser_t *parser)
{
    grocommand_t grocommand = {0, 0};
    int res = 0;

    grocommand.tab_command = NULL;
    grocommand.nb_command = 0;
    grocommand.tab_command = NULL;

    if (( res = fill_tab_command(parser, &grocommand)) == ERROR){
        parser->error = ERROR;
        return (grocommand_t){0, 0};
    }
    return grocommand;
}
