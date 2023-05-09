/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** peek_get
*/

#include "parser/lexer.h"

char lexer_get(lexer_t *lex)
{
    if (!lex)
        return 0;
    lex->cursor += 1;
    lex->context = 0;
    return lex->input[lex->cursor - 1];
}

char lexer_peek(lexer_t *lex)
{
    if (!lex)
        return 0;
    return lex->input[lex->cursor];
}
