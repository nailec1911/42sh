/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** get_grocommand
*/

#include <stdlib.h>
#include "parser/create_ast.h"
#include "macro_errors.h"

static int add_elt_in_tab(grocommand_t *grocommand, or_command_t new_command)
{
    or_command_t * temp = grocommand->tab_or_command;

    if ((grocommand->tab_or_command =
    malloc(sizeof(or_command_t) * (grocommand->nb_or_command+ 1))) == NULL)
        return ERROR;

    for (int i = 0; i < grocommand->nb_or_command- 1; i += 1)
        grocommand->tab_or_command[i] = temp[i];

    grocommand->tab_or_command[grocommand->nb_or_command- 1] = new_command;
    grocommand->tab_or_command[grocommand->nb_or_command].nb_and_command = -1;
    if (temp != NULL)
        free(temp);
    return SUCCESS;
}

static int fill_tab_command(parser_t *parser, grocommand_t *grocommand)
{
    grocommand->nb_or_command = 1;
    if (add_elt_in_tab(grocommand, get_or_command(parser)) == ERROR) {
        parser->error = ERROR;
        return ERROR;
    }
    while (!END_GRO_CMD(PEEK(parser)) && parser->error == SUCCESS) {
        parser->cursor += 1;
        grocommand->nb_or_command += 1;
        if (add_elt_in_tab(grocommand, get_or_command(parser)) == ERROR)
            parser->error = ERROR;
        if (parser->error != 0)
            return parser->error;
        if (!END_GRO_CMD(PEEK(parser))
        && PEEK(parser).type != OPERATOR_OR) {
            parser->error = FAILURE;
            return parser->error;
        }
    }
    return SUCCESS;
}

grocommand_t get_grocommand(parser_t *parser)
{
    grocommand_t grocommand = {0, 0};
    int res = 0;

    if (!parser)
        return grocommand;
    grocommand.tab_or_command = NULL;
    grocommand.nb_or_command = 0;

    if (( res = fill_tab_command(parser, &grocommand)) == ERROR){
        parser->error = ERROR;
        return (grocommand_t){0, 0};
    }
    return grocommand;
}
