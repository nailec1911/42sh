/*
** EPITECH PROJECT, 2023
** merge_jib
** File description:
** replace_var
*/

#include "mysh.h"
#include "str_func.h"
#include "macro_errors.h"

static int get_index_var(token_t *token, int i, int *start, int *end)
{
    if (token->value[i] == '$') {
        *start = i;
        *end = *start;
        while (is_in(token->value[*end + 1], " \t|;()") != 0
        && *end < token->size_val)
            *end += 1;
    }
    return i;
}

int replace_var(mysh_t *mysh, token_t *token)
{
    int start = 0;
    int end = 0;
    return SUCCESS;
    if (token->value[0] == '\'' || token->value[0] == '`')
        return SUCCESS;

    for (int i = 0; i < token->size_val; i += 1) {
        i = get_index_var(token, i, &start, &end);
    }
    printf("%d, %d\n", start, end);
    return SUCCESS;
}
