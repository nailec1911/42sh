/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** parse_input
*/

#include <stdlib.h>
#include "parser/parse.h"
#include "mysh.h"
#include "macro_errors.h"

static int get_ast(mysh_t *mysh, char *input)
{
    int res = 0;
    token_t *list_token = lexer(input);

    free(input);
    if (list_token == NULL)
        return ERROR;
    res = create_ast(list_token, &(mysh->ast));
    if (res == FAILURE) {
        free_ast(mysh->ast);
        mysh->last_status = 1;
    }
    if (res == ERROR)
        mysh->last_status = ERROR;
    free(list_token);
    return res;
}

int parse_input(char *input, mysh_t *mysh)
{
    int res = 0;

    if ((res = get_ast(mysh, input)) != SUCCESS)
        return res;
    if ((res = set_all_ast(&(mysh->ast))) != SUCCESS) {
        mysh->last_status = res;
        return res;
    }

    return SUCCESS;
}
