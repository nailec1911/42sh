/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** quote_and_inhib
*/

#include <stdlib.h>
#include <string.h>
#include "str_func.h"
#include "parser/parse.h"
#include "handle_input.h"
#include "mysh.h"
#include "macro_errors.h"

static token_t *remove_quote(mysh_t *mysh, token_t *list, int i)
{
    char type = list[i].value[0];

    list[i].value[list[i].size_val - 1] = '\0';
    for (int j = 0; j < list[i].size_val - 1; j += 1)
        list[i].value[j] = list[i].value[j + 1];
    if (type == '`') {
        list[i].value[strlen(list[i].value)] = '`';
        return replace_magic(mysh, list, i);
    }
    return list;
}

static token_t *remove_quote_and_inhib(mysh_t *mysh, token_t *list, int i)
{
    if (replace_var(mysh, &list[i]) == ERROR)
        return NULL;
    if (is_in(list[i].value[0], QUOTED) != 0) {
        if (remove_inhibitors(list[i].value) == ERROR)
            return NULL;
        return list;
    }
    return remove_quote(mysh, list, i);
}

token_t *quote_and_inhib(mysh_t *mysh, token_t *list)
{
    for (int i = 0; list[i].type != END_LINE; i += 1) {
        if (list[i].type == IDENTIFIER
        && (list = remove_quote_and_inhib(mysh, list, i)) == NULL)
            return NULL;
    }
    return list;
}
