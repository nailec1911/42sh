/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_input
*/

#include <string.h>
#include <stdlib.h>
#include "parser/parse.h"
#include "mysh.h"
#include "macro_errors.h"
int tokens_to_history(mysh_t *mysh, token_t *list);
token_t *loop_for_aliases(mysh_t *mysh, token_t *list);


int handle_input(mysh_t *mysh, char *input)
{
    token_t *list_token = lexer(input);

    if (list_token == NULL)
        return ERROR;
    if (tokens_to_history(mysh, list_token) == ERROR)
        return ERROR;
    if ((list_token = loop_for_aliases(mysh, list_token)) == NULL)
        return ERROR;
    free(input);
    return SUCCESS;
}
