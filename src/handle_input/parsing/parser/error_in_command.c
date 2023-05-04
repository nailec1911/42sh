/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** error_in_command
*/

#include <stdlib.h>
#include <stdio.h>
#include "macro_errors.h"
#include "parser/parse.h"

void error_redirect(int type)
{
    if (type == REDIRECT_IN_1 || type == REDIRECT_IN_2)
        fprintf(stderr, "Ambiguous input redirect.\n");
    if (type == REDIRECT_OUT_1 || type == REDIRECT_OUT_2)
        fprintf(stderr, "Ambiguous output redirect.\n");
}

void check_error(parser_t *parser, command_t new)
{
    if (parser->error != 0)
        return;
    if (new.nb_command != 0 && new.is_ast == true) {
        parser->error = 1;
        fprintf(stderr, "Badly placed ()'s.\n");
        return;
    }
    if (new.args== NULL && new.is_ast == false) {
        parser->error = 1;
        fprintf(stderr, "Invalid null command.\n");
        return;
    }
}
