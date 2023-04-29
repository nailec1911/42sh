/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** quoted_tokens
*/

#include <stdlib.h>
#include <stdio.h>
#include "str_func.h"
#include "parser/lexer.h"

static void set_new(lexer_t *lex, token_t *new, char quote)
{
    if (quote == '`')
        new->size_val += 1;
    if ((new->value = malloc(sizeof(char) * (new->size_val + 1))) == NULL) {
        new->type = T_ERROR;
        return;
    }
    for (int i = 0; i < new->size_val; i += 1)
        new->value[i] = lexer_get(lex);
    new->value[new->size_val] = '\0';

    if (quote != '`')
        lexer_get(lex);
}

token_t quoted_tokens(lexer_t *lex)
{
    token_t new = {IDENTIFIER, 0, 0};
    char quote = lexer_get(lex);
    int temp_cursor = lex->cursor;

    while (lexer_peek(lex) != quote && lexer_peek(lex) != '\n') {
        new.size_val += 1;
        lex->cursor += 1;
    }
    if (lexer_peek(lex) == '\n') {
        fprintf(stderr, "Unmatched '%c'.\n", quote);
        new.type = UNMATCHED_QUOTE;
    }
    lex->cursor = temp_cursor;
    set_new(lex, &new, quote);
    return new;
}
