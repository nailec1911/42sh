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
    for (int i = start + end; src[i]; ++ i)
        res[ind ++] = src[i];
    res[ind] = '\0';
    free(src);
    return res;
}

static char *get_var_str(mysh_t *mysh, char *name)
{
    vars_t *var = get_global_var_by_name(mysh->vars, name);

    if (var == NULL) {
        fprintf(stderr, "%s: Undefined variable.\n", name);
        mysh->last_status = 1;
        return NULL;
    }
    return var->buffer;
}

static char *get_new_str_value(mysh_t *mysh, char *str, int from, int to)
{
    char *name = calloc(to, 0);
    int offset = from + 1;
    char *var_str = NULL;

    if (name == NULL)
        return str;
    for (int i = 0; i < to - 1 && str[i + offset] != '}'; i += 1) {
        if (str[i + offset] == '{') {
            offset += 1;
            to += 1;
        }
        name[i] = str[i + offset];
    }
    var_str = get_var_str(mysh, name);
    free(name);
    if (var_str == NULL)
        return str;
    return insert_str(str, var_str, from, to);
}

static char *get_index_var(mysh_t *mysh, char *str, int *i)
{
    int len = 1;

    if (str[*i] == '\\') {
        *i += 1;
        return str;
    }
    if (str[*i] == '$') {
        while (is_in(str[*i + len], " \t|&$;()}<>\n") != 0
        && str[*i + len] != '\0')
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
