/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** tokens_to_history
*/

#include <stdlib.h>
#include "macro_errors.h"
#include "mysh.h"
#include "handle_input.h"

static int get_size_malloc(token_t *list)
{
    int size = 0;

    for (int i = 0; list[i].type != END_LINE; i += 1) {
        if (list[i].type == T_ERROR)
            return -1;
        size += list[i].size_val + 1;
    }
    return size;
}

static char *get_str_for_history(token_t *list)
{
    int size = get_size_malloc(list);
    char *res = NULL;
    int j = 0;

    if (size <= 0)
        return NULL;
    if ((res = calloc(size + 1, sizeof(char))) == NULL)
        return NULL;
    for (int i = 0; list[i].type != END_LINE; i += 1) {
        for (int k = 0; k < list[i].size_val; k += 1) {
            res[j] = list[i].value[k];
            j += 1;
        }
        res[j] = ' ';
        j += 1;
    }
    res[j - 1] = '\n';
    res[j] = '\0';
    return res;
}

int tokens_to_history(mysh_t *mysh, token_t *list)
{
    char *to_history = get_str_for_history(list);

    for (int i = 0; list[i].type != END_LINE; i += 1) {
        if (list[i].type == UNMATCHED_QUOTE || list[i].type == T_ERROR) {
            mysh->last_status = 1;
            return SUCCESS;
        }
    }
    if (to_history == NULL)
        return ERROR;
    if (mysh->display_line) {
        printf("%s", to_history);
        fflush(stdout);
    }
    if (add_in_history(&mysh->history, to_history) == ERROR)
        return ERROR;
    free(to_history);
    return SUCCESS;
}
