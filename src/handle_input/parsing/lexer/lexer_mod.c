/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** lexer_mod
*/

#include "parser/lexer.h"

char lexer_get(lexer_t *lex)
{
    lex->cursor += 1;
    return lex->input[lex->cursor - 1];
}

char lexer_peek(lexer_t *lex)
{
    return lex->input[lex->cursor];
}
