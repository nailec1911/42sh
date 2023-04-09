/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** single_or_mul_char_tokens
*/

#include "parser/lexer.h"


token_t token_redirect_in(lexer_t *lex)
{
    token_t new = {0, 0, 0};

    lexer_get(lex);

    new.type = REDIRECT;
    new.size_val = 1;
    if (lexer_peek(lex) == '<') {
        lexer_get(lex);
        new.type = REDIRECT;
        new.size_val = 2;
    }
    return new;
}

token_t token_redirect_out(lexer_t *lex)
{
    token_t new = {0, 0, 0};

    lexer_get(lex);

    new.type = REDIRECT;
    new.size_val = 3;
    if (lexer_peek(lex) == '>') {
        lexer_get(lex);
        new.size_val = 4;
        new.type = REDIRECT;
    }
    return new;
}

token_t token_pipe(lexer_t *lex)
{
    token_t new = {0, 0, 0};

    lexer_get(lex);
    new.type = PIPE;
    if (lexer_peek(lex) == '|') {
        lexer_get(lex);
        new.type = OPERATOR_OR;
    }
    return new;
}

token_t token_and(lexer_t *lex)
{
    token_t new = {0, 0, 0};

    lexer_get(lex);
    new.type = AND;
    if (lexer_peek(lex) == '&') {
        lexer_get(lex);
        new.type = OPERATOR_AND;
    }
    return new;
}
