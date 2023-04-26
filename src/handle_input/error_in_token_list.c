/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** error_in_token_list
*/

#include <stdlib.h>
#include "mysh.h"
#include "macro_errors.h"

static int error_parenthesis(mysh_t *mysh, int parenthesis)
{
    if (parenthesis > 0)
        fprintf(stderr, "Too many ('s.\n");
    if (parenthesis < 0)
        fprintf(stderr, "Too many )'s.\n");
    if (parenthesis != 0) {
        mysh->last_status = FAILURE;
        return FAILURE;
    }
    return SUCCESS;
}

static bool is_error_token(mysh_t *mysh, token_t *list, int i)
{
    if (list[i].type == ERROR) {
        free(list);
        mysh->last_status = ERROR;
        return true;
    }
    if (list[i].type == UNMATCHED_QUOTE) {
        free(list);
        mysh->last_status = FAILURE;
        return true;
    }
    return false;
}

int error_in_tokens(mysh_t *mysh, token_t *list)
{
    int parenthesis = 0;

    if (list == NULL)
        return ERROR;
    for (int i = 0; list[i].type != END_LINE && parenthesis >= 0; i += 1) {
        if (is_error_token(mysh, list, i))
            return mysh->last_status;
        if (list[i].type == L_PARENTHESIS)
            parenthesis += 1;
        if (list[i].type == R_PARENTHESIS)
            parenthesis -= 1;
    }
    return error_parenthesis(mysh, parenthesis);
}
