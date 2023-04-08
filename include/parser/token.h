/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** token
*/

#ifndef TOKEN_H_
    #define TOKEN_H_

    typedef enum {
        END_LINE,
        NOTHING,
        SEMICOLON,
        PIPE,
        REDIRECT,
        IDENTIFIER,
        T_ERROR
    } tokentype_t;

    typedef struct token_s {
        tokentype_t type;
        char *value;
        int size_val;
    } token_t;

#endif /* !TOKEN_H_ */
