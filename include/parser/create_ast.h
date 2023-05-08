/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** create_ast
*/

#ifndef CREATE_AST_H_
    #define CREATE_AST_H_

    #include "parser/ast.h"

    typedef struct parser_s {
        token_t *list_tokens;
        int cursor;
        int error;
    } parser_t;

    #define END_AST(token) \
        ((token).type == END_LINE || (token).type == R_PARENTHESIS)

    #define END_GRO_CMD(token) \
        (END_AST(token) || (token).type == SEMICOLON)

    #define END_OR_CMD(token) \
        (END_GRO_CMD(token) || (token).type == OPERATOR_OR)

    #define END_AND_CMD(token) \
        (END_OR_CMD(token) || (token).type == OPERATOR_AND \
|| (token).type == BG)

    #define END_CMD(token) \
        (END_AND_CMD(token) || (token).type == PIPE)


    #define PEEK(parser) ((parser)->list_tokens[(parser)->cursor])

grocommand_t get_grocommand(parser_t *parser);
or_command_t get_or_command(parser_t *parser);
and_command_t get_and_command(parser_t *parser);
command_t get_command(parser_t *parser);
int get_ast_parenthesis(parser_t *parser, command_t *new);
void error_redirect(int type);
void check_error(parser_t *parser, command_t new);

#endif /* !CREATE_AST_H_ */
