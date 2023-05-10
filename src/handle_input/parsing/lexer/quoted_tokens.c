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
    if ((new->value = malloc(sizeof(char) * (new->size_val + 1))) == NULL) {
        new->type = T_ERROR;
        return;
    }
    new->value[0] = quote;
    for (int i = 1; i < new->size_val; i += 1)
        new->value[i] = lexer_get(lex);
    new->value[new->size_val] = '\0';
}

token_t quoted_tokens(lexer_t *lex)
{
    token_t new = {IDENTIFIER, 0, 1};
    char quote = lexer_get(lex);
    int temp_cursor = lex->cursor;

    if (!lex) {
        new.type = T_ERROR;
        return new;
    }
    while (lexer_peek(lex) != quote && lexer_peek(lex) != '\n') {
        new.size_val += 1;
        lex->cursor += 1;
    }
    if (lexer_peek(lex) == '\n') {
        fprintf(stderr, "Unmatched '%c'.\n", quote);
        new.type = UNMATCHED_QUOTE;
        new.value = &quote;
        new.size_val -= 1;
    }
    new.size_val += 1;
    lex->cursor = temp_cursor;
    set_new(lex, &new, quote);
    return new;
}
