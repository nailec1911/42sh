/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** lexer
*/

#include "parser/lexer.h"
#include "str_func.h"
#include "macro_errors.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

static token_t single_char_token(lexer_t *lex)
{
    if (lexer_peek(lex) == '\n')
        return token_end_line(lex);
    if (lexer_peek(lex) == '<')
        return token_redirect_in(lex);
    if (lexer_peek(lex) == '>')
        return token_redirect_out(lex);
    if (lexer_peek(lex) == '|')
        return token_pipe(lex);
    if (lexer_peek(lex) == '&')
        return token_and(lex);
    if (lexer_peek(lex) == '(')
        return token_l_parenthesis(lex);
    if (lexer_peek(lex) == ')')
        return token_r_parenthesis(lex);
    return token_semicolon(lex);
}

static token_t get_token(lexer_t *lex)
{
    while (lexer_peek(lex) == '\t' || lexer_peek(lex) == ' ')
        lexer_get(lex);
    if (lexer_peek(lex) == '\\')
        return multiple_char_token(lex);
    if (is_in(lexer_peek(lex), SINGLE_CHAR) == 0)
        return single_char_token(lex);
    if (is_in(lexer_peek(lex), QUOTED) == 0)
        return quoted_tokens(lex);
    return multiple_char_token(lex);
}

static token_t *add_elt_in_tab(lexer_t *lex, token_t to_add, token_t *old)
{
    token_t *new;
    lex->nb_token += 1;

    if (to_add.type == T_ERROR)
        return NULL;
    if ((new = malloc(sizeof(token_t) * lex->nb_token)) == NULL)
        return NULL;
    for (int i = 0; i < lex->nb_token - 1; i += 1)
        new[i] = old[i];
    new[lex->nb_token - 1] = to_add;
    if (old != NULL)
        free(old);
    return new;
}

token_t *lexer(char *input)
{
    lexer_t lex = {input, 0, 0, 0, 0};
    token_t *list_token = NULL;

    if (input == NULL)
        return NULL;
    for (; lex.input[lex.len_input] != '\n'; lex.len_input += 1);
    while ((lex.nb_token < 1 || list_token[lex.nb_token - 1].type != END_LINE)
    && lex.cursor <= lex.len_input) {
        if ((list_token =
        add_elt_in_tab(&lex, get_token(&lex), list_token)) == NULL)
            return NULL;
    }
    return list_token;
}
