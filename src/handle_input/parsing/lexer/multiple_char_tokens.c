/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** multiple_char_tokens
*/

#include <stdlib.h>
#include "str_func.h"
#include "parser/lexer.h"

token_t multiple_char_token(lexer_t *lex)
{
    token_t new = {IDENTIFIER, 0, 0};
    int temp_cursor = lex->cursor;

    while (is_in(lexer_peek(lex), SEPARATORS) != 0) {
        new.size_val += 1;
        lex->cursor += 1;
    }
    lex->cursor = temp_cursor;

    if ((new.value = malloc(sizeof(char) * (new.size_val + 1))) == NULL) {
        new.type = T_ERROR;
        return new;
    }
    for (int i = 0; i < new.size_val; i += 1)
        new.value[i] = lexer_get(lex);
    new.value[new.size_val] = '\0';
    return new;
}
