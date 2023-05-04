/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set_new_tab
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "magic_quote.h"
#include "macro_errors.h"
#include "str_func.h"

static int add_elt_in_tab(char ***tab, char *new_elt, int nb_elt)
{
    char **temp = *tab;

    if ((*tab = malloc(sizeof(char *) * (nb_elt + 1))) == NULL)
        return ERROR;
    for (int i = 0; i < nb_elt - 1; i += 1)
        (*tab)[i] = temp[i];
    if (((*tab)[nb_elt - 1] = strdup(new_elt)) == NULL)
        return ERROR;
    (*tab)[nb_elt] = NULL;
    if (temp != NULL)
        free(temp);
    return SUCCESS;
}

static int keep_old_from_to(command_t *command, char ***new, int from, int to)
{
    for (int i = from; command->args[i] != NULL && i != to; i += 1){
        command->nb_command += 1;
        if (add_elt_in_tab(new, command->args[i], command->nb_command)
            == ERROR)
            return ERROR;
    }
    return SUCCESS;
}

int set_new_tab(command_t *command, FILE *res, int ind)
{
    size_t len = 0;
    ssize_t size = 0;
    char *line = NULL;
    char **new = NULL;

    command->nb_command = 0;
    if (keep_old_from_to(command, &new, 0, ind) == ERROR)
        return ERROR;
    while ((size = getline(&line, &len, res)) != -1) {
        command->nb_command += 1;
        line[size - 1] = '\0';
        if (add_elt_in_tab(&new, line, command->nb_command) == ERROR)
            return ERROR;
    }
    if (keep_old_from_to(command, &new, ind + 1, -1) == ERROR)
        return ERROR;
    free_array(command->args);
    free(line);
    command->args = new;
    return SUCCESS;
}
