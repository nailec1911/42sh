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
        AND,
        OPERATOR_AND,
        OPERATOR_OR,
        PIPE,
        REDIRECT_IN_1,
        REDIRECT_IN_2,
        REDIRECT_OUT_1,
        REDIRECT_OUT_2,
        IDENTIFIER,
        UNMATCHED_QUOTE,
        T_ERROR
    } tokentype_t;

    #define IS_REDIRECT_IN(val) val == REDIRECT_IN_1 || val == REDIRECT_IN_2
    #define IS_REDIRECT_OUT(val) val == REDIRECT_OUT_1 || val == REDIRECT_OUT_2
    #define IS_REDIRECT(val) IS_REDIRECT_IN(val) || IS_REDIRECT_OUT(val)

    typedef struct token_s {
        tokentype_t type;
        char *value;
        int size_val;
    } token_t;

#endif /* !TOKEN_H_ */
