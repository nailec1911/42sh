/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** test_function
*/

#include <stdio.h>
#include <string.h>
#include "macro_errors.h"
#include "mysh.h"
#include "parser/parse.h"

int get_ast(mysh_t *mysh, char *input)
{
    token_t *list_token = NULL;
    char *input_test = strdup(input);
    int res = 0;

    list_token = lexer(input_test);

    res = create_ast(list_token, &(mysh->ast));
    if (res != SUCCESS){
        mysh->last_status = res;
        return res;
    }

    res = set_all_ast(&(mysh->ast));
    if (res != SUCCESS){
        mysh->last_status = res;
        return res;
    }
    return SUCCESS;
}
