/*
** EPITECH PROJECT, 2023
** merge_jib
** File description:
** replace_magic
*/

#include "mysh.h"
#include "macro_errors.h"
#include "handle_input.h"
#include "magic_quote.h"

static char **get_new_params(mysh_t *mysh, token_t *token)
{
    FILE *res_cmd = get_file_res_command(mysh, token->value);
    char **res_array = NULL;

    if (res_cmd == NULL)
        return NULL;
    if ((res_array = file_stream_to_tab(res_cmd)) == NULL)
        return NULL;
    return res_array;
}

token_t *replace_magic(mysh_t *mysh, token_t *list, int i)
{
    char **res = get_new_params(mysh, &(list[i]));

    if (res == NULL)
        return NULL;
    for (int i = 0; res[i] != NULL; i += 1)
        printf("%s\n", res[i]);
    printf("%s\n", list[i].value);
    return list;
}
