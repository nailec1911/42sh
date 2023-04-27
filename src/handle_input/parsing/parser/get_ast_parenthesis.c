/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_ast_parenthesis
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "macro_errors.h"
#include "parser/create_ast.h"
int create_ast(parser_t *parser, ast_t *ast);

int get_ast_parenthesis(parser_t *parser, command_t *new)
{
    if (new->is_ast == true) {
        parser->error = 1;
        fprintf(stderr, "Too many )'s.\n");
        return true;
    }
    if ((new->parenthesis = malloc(sizeof(ast_t))) == NULL) {
        parser->error = ERROR;
        return parser->error;
    }
    parser->cursor += 1;
    if (create_ast(parser, new->parenthesis) != SUCCESS)
        return parser->error;
    new->is_ast = true;
    parser->cursor += 1;
    return SUCCESS;
}
