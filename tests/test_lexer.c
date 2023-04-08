/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** test_lexer
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "parser/lexer.h"
#include "macro_errors.h"
token_t *lexer(char *input);

Test(lexer1, only_ls){
    token_t *tokens = lexer("ls\n");

    cr_assert_eq(tokens[0].type, IDENTIFIER);
    cr_assert_str_eq(tokens[0].value, "ls");
    cr_assert_eq(tokens[1].type, END_LINE);
}

Test(lexer2, ls_with_args){
    token_t *tokens = lexer("ls -l -a\n");

    cr_assert_eq(tokens[0].type, IDENTIFIER);
    cr_assert_str_eq(tokens[0].value, "ls");
    cr_assert_eq(tokens[1].type, IDENTIFIER);
    cr_assert_str_eq(tokens[1].value, "-l");
    cr_assert_eq(tokens[2].type, IDENTIFIER);
    cr_assert_str_eq(tokens[2].value, "-a");
    cr_assert_eq(tokens[3].type, END_LINE);
}

Test(lexer3, lot_of_tab_and_space){
    token_t *tokens = lexer("ls    \t   -l   \t\t           -a\n");

    cr_assert_eq(tokens[0].type, IDENTIFIER);
    cr_assert_str_eq(tokens[0].value, "ls");
    cr_assert_eq(tokens[1].type, IDENTIFIER);
    cr_assert_str_eq(tokens[1].value, "-l");
    cr_assert_eq(tokens[2].type, IDENTIFIER);
    cr_assert_str_eq(tokens[2].value, "-a");
    cr_assert_eq(tokens[3].type, END_LINE);
}

Test(lexer4, multiple_grocomands){
    token_t *tokens = lexer("ls -l; cd src; ls\n");

    cr_assert_eq(tokens[0].type, IDENTIFIER);
    cr_assert_str_eq(tokens[0].value, "ls");
    cr_assert_eq(tokens[1].type, IDENTIFIER);
    cr_assert_str_eq(tokens[1].value, "-l");
    cr_assert_eq(tokens[2].type, SEMICOLON);
    cr_assert_eq(tokens[3].type, IDENTIFIER);
    cr_assert_str_eq(tokens[3].value, "cd");
    cr_assert_eq(tokens[4].type, IDENTIFIER);
    cr_assert_str_eq(tokens[4].value, "src");
    cr_assert_eq(tokens[5].type, SEMICOLON);
    cr_assert_eq(tokens[6].type, IDENTIFIER);
    cr_assert_str_eq(tokens[6].value, "ls");
    cr_assert_eq(tokens[7].type, END_LINE);
}

Test(lexer5, lotof_semicolon){
    token_t *tokens = lexer(";;ls -l;; cd src;\n");

    cr_assert_eq(tokens[0].type, SEMICOLON);
    cr_assert_eq(tokens[1].type, SEMICOLON);

    cr_assert_eq(tokens[2].type, IDENTIFIER);
    cr_assert_str_eq(tokens[2].value, "ls");
    cr_assert_eq(tokens[3].type, IDENTIFIER);
    cr_assert_str_eq(tokens[3].value, "-l");
    cr_assert_eq(tokens[4].type, SEMICOLON);
    cr_assert_eq(tokens[5].type, SEMICOLON);
    cr_assert_eq(tokens[6].type, IDENTIFIER);
    cr_assert_str_eq(tokens[6].value, "cd");
    cr_assert_eq(tokens[7].type, IDENTIFIER);
    cr_assert_str_eq(tokens[7].value, "src");
    cr_assert_eq(tokens[8].type, SEMICOLON);
    cr_assert_eq(tokens[9].type, END_LINE);
}

Test(lexer6, pipe){
    token_t *tokens = lexer("ls | ls |ls\n");

    cr_assert_eq(tokens[0].type, IDENTIFIER);
    cr_assert_str_eq(tokens[0].value, "ls");
    cr_assert_eq(tokens[1].type, PIPE);
    cr_assert_eq(tokens[2].type, IDENTIFIER);
    cr_assert_str_eq(tokens[2].value, "ls");
    cr_assert_eq(tokens[3].type, PIPE);
    cr_assert_eq(tokens[4].type, IDENTIFIER);
    cr_assert_str_eq(tokens[4].value, "ls");
    cr_assert_eq(tokens[5].type, END_LINE);
}


Test(lexer7, redirect){
    token_t *tokens = lexer(">><< < > temp\n");

    cr_assert_eq(tokens[0].type, REDIRECT);
    cr_assert_eq(tokens[1].type, REDIRECT);
    cr_assert_eq(tokens[2].type, REDIRECT);
    cr_assert_eq(tokens[3].type, REDIRECT);
    cr_assert_eq(tokens[4].type, IDENTIFIER);
    cr_assert_str_eq(tokens[4].value, "temp");
    cr_assert_eq(tokens[5].type, END_LINE);
}

Test(lexer8, empty){
    token_t *tokens = lexer("\n");

    cr_assert_eq(tokens[0].type, END_LINE);
}