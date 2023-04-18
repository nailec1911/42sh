/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** free_env
*/

#include <stdlib.h>
#include "mysh.h"
#include <unistd.h>

void free_env(mysh_t *mysh)
{
    env_var_t *to_free;
    env_var_t *temp = mysh->list_env;

    while (temp != NULL) {
        to_free = temp;
        temp = temp->next;
        free(to_free->var);
        free(to_free);
    }
    fclose(mysh->history->fd_file);
    close(mysh->history->fd_history_file);
    fclose(mysh->alias->fd_file);
    close(mysh->alias->fd_alias_file);
}
