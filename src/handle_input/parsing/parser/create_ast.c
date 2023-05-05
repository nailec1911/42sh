/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** create_ast
*/

#include <stdlib.h>
#include "parser/create_ast.h"
#include "macro_errors.h"

static int add_elt_in_tab(ast_t *ast, grocommand_t new_command)
{
    grocommand_t * temp = ast->tab_grocommands;

    if ((ast->tab_grocommands =
    malloc(sizeof(grocommand_t) * (ast->nb_grocommand + 1))) == NULL)
        return ERROR;
    for (int i = 0; i < ast->nb_grocommand - 1; i += 1)
        ast->tab_grocommands[i] = temp[i];
    ast->tab_grocommands[ast->nb_grocommand - 1] = new_command;
    ast->tab_grocommands[ast->nb_grocommand].nb_or_command = -1;
    if (temp != NULL)
        free(temp);
    return SUCCESS;
}

static int fill_tab_grocommand(parser_t *parser, ast_t *ast)
{
    while (!END_AST(PEEK(parser)) && parser->error == SUCCESS) {
        while (PEEK(parser).type == SEMICOLON)
            parser->cursor += 1;
        if (PEEK(parser).type == END_LINE)
            return SUCCESS;
        ast->nb_grocommand += 1;
        if (add_elt_in_tab(ast, get_grocommand(parser)) == ERROR)
            parser->error = ERROR;
        if (parser->error != 0)
            return parser->error;
        if (!END_GRO_CMD(PEEK(parser))) {
            parser->error = FAILURE;
            return parser->error;
        }
    }
    return SUCCESS;
}

int create_ast(parser_t *parser, ast_t *ast)
{
    ast->nb_grocommand = 0;
    ast->tab_grocommands = NULL;
    if (fill_tab_grocommand(parser, ast) == ERROR) {
        return ERROR;
    }
    return parser->error;
}
