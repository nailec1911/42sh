/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** test_function
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "macro_errors.h"
#include "mysh.h"
#include "parser/parse.h"

int get_ast(mysh_t *mysh, char *input)
{
    parser_t parser;
    char *input_test = strdup(input);
    int res = 0;

    parser.list_tokens = lexer(input_test);

    mysh->ast.tab_grocommands = NULL;
    mysh->ast.nb_grocommand = 0;
    mysh->ast = (ast_t){0, NULL};
    res = create_ast(&parser, &(mysh->ast));
    if (res != SUCCESS){
        mysh->last_status = res;
        return res;
    }
    free(parser.list_tokens);
    res = set_all_ast(&(mysh->ast));
    if (res != SUCCESS){
        mysh->last_status = res;
        return res;
    }
    return SUCCESS;
}
