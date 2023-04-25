/*
** EPITECH PROJECT, 2023
** test
** File description:
** loop_exclamation_mark
*/

#include <stdlib.h>
#include <string.h>
#include "parser/parse.h"
#include "handle_input.h"
#include "mysh.h"
char *do_exclamation_mark(mysh_t *mysh, char *input);

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
    for (int j = 0; j < len_new - 1; j += 1)
        new[i ++] = to_add[j];
    for (int j = ind + 1; j < len_old; j += 1)
        new[i ++] = old[j];
    free(old);
    return new;
}

static bool need_changes(token_t *list, int *i)
{
    if (list[*i].type != IDENTIFIER)
        return false;
    if (list[*i].value[0] != '!')
        return false;
    if (list[*i].value[1] == '\n' || list[*i].value[1] == '\0')
        return false;
    if (list[*i].value[1] == '!') {
        *i += 1;
        return false;
    }
    return true;
}

static token_t *replace_if_exclamation_mark(mysh_t *mysh, token_t *list, int *i)
{
    char *new = NULL;
    token_t *list_new;
    if (!need_changes(list, i))
        return list;
    mysh->display_line = true;
    new = do_exclamation_mark(mysh, list[*i].value);
    if (new == NULL || strcmp(new, list[*i].value) == 0)
        return list;
    if ((list_new = lexer(new)) == NULL)
        return NULL;
    free(list[*i].value);
    list = get_new_tab(list, list_new, *i);
    free(list_new);
    free(new);
    *i -= 1;
    return list;
}

token_t *loop_for_exclamation_mark(mysh_t *mysh, token_t *list)
{
    for (int i = 0; list[i].type != END_LINE
    && mysh->last_status != 1; i += 1) {
        if ((list = replace_if_exclamation_mark(mysh, list, &i)) == NULL)
            return NULL;
    }
    return list;
}
