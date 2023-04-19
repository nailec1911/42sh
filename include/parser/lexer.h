/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** lexer
*/

#ifndef LEXER_H_
    #define LEXER_H_

    #include "token.h"

    #define SEPARATORS ";&><| \t\n\0"
    #define SINGLE_CHAR ";&><|\n"
    #define QUOTED "'\"(`"

    typedef struct lexer_s {
        char *input;
        int len_input;
        int cursor;
        int nb_token;
        int context;
    } lexer_t;

    char lexer_peek(lexer_t *lex);
    char lexer_get(lexer_t *lex);
    token_t token_redirect_in(lexer_t *lex);
    token_t token_redirect_out(lexer_t *lex);
    token_t token_pipe(lexer_t *lex);
    token_t token_and(lexer_t *lex);
    token_t token_semicolon(lexer_t *lex);
    token_t token_end_line(lexer_t *lex);
    token_t multiple_char_token(lexer_t *lex);
    token_t quoted_tokens(lexer_t *lex);

#endif /* !LEXER_H_ */
