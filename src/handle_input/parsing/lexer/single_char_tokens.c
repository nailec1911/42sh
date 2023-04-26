/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** single_char_tokens
*/

#include "parser/lexer.h"

token_t token_semicolon(lexer_t *lex)
{
    token_t new = {0, ";", 0};

    lexer_get(lex);

    new.type = SEMICOLON;
    new.size_val = 1;
    return new;
}

token_t token_end_line(lexer_t *lex)
{
    token_t new = {0, "\n", 0};

    lexer_get(lex);

    new.type = END_LINE;
    new.size_val = 1;
    return new;
}

token_t token_l_parenthesis(lexer_t *lex)
{
    token_t new = {0, "(", 0};

    lexer_get(lex);

    new.type = L_PARENTHESIS;
    new.size_val = 1;
    return new;
}

token_t token_r_parenthesis(lexer_t *lex)
{
    token_t new = {0, ")", 0};

    lexer_get(lex);

    new.type = R_PARENTHESIS;
    new.size_val = 1;
    return new;
}
