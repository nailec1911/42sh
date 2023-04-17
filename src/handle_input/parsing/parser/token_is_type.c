/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** token_is_type
*/

#include "parser/ast.h"

bool is_end_command(token_t token)
{
    if (token.type == END_LINE
    || token.type == SEMICOLON
    || token.type == OPERATOR_AND
    || token.type == OPERATOR_OR
    || token.type == UNMATCHED_QUOTE)
        return true;
    return false;
}
