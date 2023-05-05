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
#include "handle_input.h"

static token_t *get_list_tokens(mysh_t *mysh, char *input)
{
    token_t *list_token = lexer(input);

    free(input);
    mysh->display_line = false;
    if (list_token == NULL)
        return NULL;
    if ((list_token = loop_for_exclamation_mark(mysh, list_token)) == NULL)
        return NULL;
    if (tokens_to_history(mysh, list_token) == ERROR)
        return NULL;
    if ((list_token = loop_for_aliases(mysh, list_token)) == NULL)
        return NULL;
    if ((list_token = quote_and_inhib(mysh, list_token)) == NULL)
        return NULL;
    return list_token;
}

static int get_ast(mysh_t *mysh, token_t *list_token)
{
    parser_t parser = {list_token, 0, 0};
    int res = create_ast(&parser, &(mysh->ast));

    if (res == FAILURE) {
        free_ast(mysh->ast);
        mysh->last_status = 1;
        free(list_token);
        return FAILURE;
    }
    if (res == ERROR)
        mysh->last_status = ERROR;
    free(list_token);
    return SUCCESS;
}

int handle_input(mysh_t *mysh, char *input)
{
    token_t *list_token = get_list_tokens(mysh, input);
    int res = 0;

    if (mysh->last_status == 1) {
        free(list_token);
        return FAILURE;
    }
    if ((res = error_in_tokens(mysh, list_token)) != SUCCESS)
        return res;
    if ((res = get_ast(mysh, list_token)) != SUCCESS)
        return res;
    if ((res = set_all_ast(&(mysh->ast))) != SUCCESS) {
        mysh->last_status = res;
        free_ast(mysh->ast);
        return res;
    }
    return SUCCESS;
}
