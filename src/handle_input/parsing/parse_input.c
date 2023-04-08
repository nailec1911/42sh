/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** parse_input
*/

#include <stdlib.h>
#include "parser/parse.h"
#include "all_args.h"
#include "macro_errors.h"

static int get_ast(all_args_t *all_args, char *input)
{
    int res = 0;
    token_t *list_token = lexer(input);

    free(input);
    if (list_token == NULL)
        return ERROR;
    res = create_ast(list_token, &(all_args->ast));
    if (res == FAILURE) {
        free_ast(all_args->ast);
        all_args->last_status = 1;
    }
    if (res == ERROR)
        all_args->last_status = ERROR;
    free(list_token);
    return res;
}

int parse_input(char *input, all_args_t *all_args)
{
    int res = 0;

    if ((res = get_ast(all_args, input)) != SUCCESS)
        return res;
    if ((res = set_all_ast(&(all_args->ast))) != SUCCESS) {
        all_args->last_status = res;
        return res;
    }

    return SUCCESS;
}
