/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** multiple_char_tokens
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "str_func.h"
#include "parser/lexer.h"

static int get_size_value(lexer_t *lex)
{
    int temp_cursor = lex->cursor;
    int size_val = 0;

    while (lex->context == 1 || (lex->cursor < lex->len_input &&
    is_in(lexer_peek(lex), SEPARATORS) != 0)) {
        size_val += 1;
        lex->cursor += 1;
        lex->context = 0;
        if (lexer_peek(lex) == '\\') {
            lex->cursor += 1;
            lex->context = 1;
        }
    }
    lex->cursor = temp_cursor;
    return size_val;
}

token_t multiple_char_token(lexer_t *lex)
{
    token_t new = {IDENTIFIER, 0, get_size_value(lex)};

    if ((new.value = malloc(sizeof(char) * (new.size_val + 1))) == NULL) {
        new.type = T_ERROR;
        return new;
    }
    for (int i = 0; i < new.size_val; i += 1) {
        if (lexer_peek(lex) == '\\')
            lexer_get(lex);
        new.value[i] = lexer_get(lex);
    }
    new.value[new.size_val] = '\0';
    return new;
}
