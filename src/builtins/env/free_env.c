/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** free_env
*/

#include <stdlib.h>
#include <unistd.h>
#include "str_func.h"
#include "mysh.h"

void free_env(mysh_t *mysh)
{
    if (mysh == NULL)
        return;

    for (int i = 0; mysh->env[i]; ++i)
        free(mysh->env[i]);
    free(mysh->env);
    fclose(mysh->history.fd_file);
    close(mysh->history.fd_history_file);
    fclose(mysh->alias.fd_file);
    close(mysh->alias.fd_alias_file);
    free(mysh->history.command);
    if (mysh->alias.tab_file != NULL) {
        free_array(mysh->alias.tab_file);
    }
    if (mysh->history.tab_hist != NULL && mysh->history.have_hist == true) {
        free_tab_hist(mysh->history.tab_hist);
    }
}
