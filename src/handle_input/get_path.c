/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** get_path
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"

static int is_absolute_path(char *path)
{
    for (int i = 0; path[i] != '\0'; i += 1) {
        if (path[i] == '/')
            return SUCCESS;
    }
    return FAILURE;
}

static int try_all_paths(char **all_prefixes, char **path)
{
    char *path_to_try = 0;

    for (int i = 0; all_prefixes[i] != NULL; i += 1) {
        if ((path_to_try =
        my_strcat_with_char(all_prefixes[i], *path, '/')) == NULL)
            return ERROR;
        if (access(path_to_try, F_OK) == 0) {
            free(*path);
            *path = path_to_try;
            return SUCCESS;
        }
        free(path_to_try);
    }
    return FAILURE;
}

int get_path(mysh_t *mysh, char **path)
{
    char *env_path = NULL;
    char **all_prefix = NULL;
    int res_all_try = 0;

    if ((*path = my_str_dup(mysh->command[0])) == NULL)
        return ERROR;
    if (is_absolute_path(*path) == SUCCESS) {
        if (access(mysh->command[0], F_OK) == 0)
            return SUCCESS;
        return FAILURE;
    }

    if ((env_path = get_env_var(mysh, "PATH=")) == NULL)
        return FAILURE;
    if ((all_prefix = input_to_array(env_path, ":")) == NULL)
        return ERROR;
    res_all_try = try_all_paths(all_prefix, path);
    free_array(all_prefix);
    return res_all_try;
}
