/*
** EPITECH PROJECT, 2023
** merge_jib
** File description:
** replace_var
*/

#include <stdlib.h>
#include <string.h>
#include "mysh.h"
#include "str_func.h"
#include "macro_errors.h"

static char *insert_str(char *src, char *to_insert, int start, int end)
{
    int len = strlen(src) + strlen(to_insert);
    char *res = calloc(len, 1);
    int ind = 0;

    if (res == NULL)
        return NULL;
    for (int i = 0; i < start; ++ i)
        res[ind ++] = src[i];
    for (int i = 0; to_insert[i]; ++ i)
        res[ind ++] = to_insert[i];
    for (int i = start + end + 1; src[i]; ++ i)
        res[ind ++] = src[i];
    res[ind] = '\0';
    free(src);
    return res;
}

static char *get_new_str_value(mysh_t *mysh, char *str, int from, int to)
{
    char *name = str + from + 1;
    vars_t *var;

    if (name[0] == '{') {
        name += 1;
        name[to - 2] = '\0';
    } else
        name[to] = '\0';
    if ((var = get_global_var_by_name(mysh->vars, name)) == NULL) {
        fprintf(stderr, "%s: Undefined variable.\n", name);
        mysh->last_status = 1;
        return str;
    }
    return insert_str(str, var->buffer, from, to);
}

static char *get_index_var(mysh_t *mysh, char *str, int *i)
{
    int len = 0;

    if (str[*i] == '\\') {
        *i += 1;
        return str;
    }
    if (str[*i] == '$') {
        while (is_in(str[*i + len], " \t|;()}") != 0 && str[*i + len] != '\0')
            len += 1;
        return get_new_str_value(mysh, str, *i, len);
    }
    return str;
}

int replace_var(mysh_t *mysh, token_t *token)
{
    token->value[token->size_val] = '\0';

    if (token->value[0] == '\'' || token->value[0] == '`')
        return SUCCESS;
    for (int i = 0; token->value[i] != '\0'
    && token->value[i + 1] != '\0'; i += 1) {
        token->value = get_index_var(mysh, token->value, &i);
    }
    return SUCCESS;
}
