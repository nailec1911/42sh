/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** loop_for_aliases
*/

#include <stdlib.h>
#include <string.h>
#include "parser/parse.h"
#include "handle_input.h"
#include "mysh.h"

static token_t *get_new_tab(token_t *old, token_t *to_add, int ind)
{
    int len_old = 0;
    int len_new = 0;
    int i = 0;
    token_t *new = NULL;

    while (old[len_old++].type != END_LINE);
    while (to_add[len_new++].type != END_LINE);
    if ((new = malloc(sizeof(token_t) *(len_old + len_new))) == NULL)
        return NULL;
    for (; i < ind; i += 1)
        new[i] = old[i];
    for (int j = 0; j < len_new - 1; j += 1) {
        new[i] = to_add[j];
        i += 1;
    }
    for (int j = ind + 1; j < len_old; j += 1) {
        new[i] = old[j];
        i += 1;
    }
    free(old);
    return new;
}

static token_t *replace_if_alias(mysh_t *mysh, token_t *list, int *i)
{
    char *alias = NULL;
    token_t *list_alias;

    if (list[*i].type != IDENTIFIER || (*i > 0 && list[*i - 1].type == IDENTIFIER))
        return list;
    if ((alias = is_alias(mysh, list[*i].value)) == NULL)
        return NULL;
    if (strcmp(alias, list[*i].value) == 0)
        return list;
    if ((list_alias = lexer(alias)) == NULL)
        return NULL;
    list = get_new_tab(list, list_alias, *i);
    free(list_alias);
    *i -= 1;
    return list;
}

token_t *loop_for_aliases(mysh_t *mysh, token_t *list)
{
    for (int i = 0; list[i].type != END_LINE; i += 1) {
        if ((list = replace_if_alias(mysh, list, &i)) == NULL)
            return NULL;
    }
    return list;
}
