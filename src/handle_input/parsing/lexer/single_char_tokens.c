/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** single_char_tokens
*/

#include "parser/lexer.h"

token_t token_semicolon(lexer_t *lex)
{
    token_t new = {0, 0, 0};

    lexer_get(lex);

    new.type = SEMICOLON;

    return new;
}

token_t token_end_line(lexer_t *lex)
{
    token_t new = {0, 0, 0};

    lexer_get(lex);

    new.type = END_LINE;

    return new;
}
