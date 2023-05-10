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
    parser_t parser = {0};
    int res = 0;

    parser.list_tokens = lexer(input);

    res = create_ast(&parser, &(mysh->ast));
    if (res != SUCCESS){
        mysh->last_status = res;
        return res;
    }
    free(parser.list_tokens);
    return SUCCESS;
}
