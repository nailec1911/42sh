/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** parse
*/

#ifndef PARSE_H_
    #define PARSE_H_

    #include "parser/lexer.h"
    #include "parser/create_ast.h"

    token_t *lexer(char *input);
    int create_ast(parser_t *parser, ast_t *ast);
    int set_all_ast(ast_t *ast);
    void free_ast(ast_t *ast);

#endif /* !PARSE_H_ */
