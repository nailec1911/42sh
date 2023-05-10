/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** get_path
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "mysh.h"
#include "builtins/env.h"
#include "str_func.h"
#include "macro_errors.h"
#include "exec_command.h"

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
    char *path_to_try = NULL;

    for (int i = 0; all_prefixes[i] != NULL; i += 1) {
        path_to_try = my_strcat_with_char(all_prefixes[i], *path, '/');
        if (path_to_try == NULL)
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

static char *get_all_path(mysh_t *mysh)
{
    char *env_path = NULL;
    char default_path[1024];

    env_path = get_env_var(mysh, "PATH=");
    if (!env_path) {
        env_path = malloc(1);
        env_path[0] = 0;
    }
    confstr(_CS_PATH, default_path, 1024);
    return my_strcat_with_char(env_path, default_path, ':');
}

int get_path(mysh_t *mysh, char **path, command_t *to_exec)
{
    char *env_path = NULL;
    char **all_prefix = NULL;
    int res_all_try = 0;

    if (!mysh || !path || !to_exec || !to_exec->args)
        return ERROR;
    if ((*path = strdup(to_exec->args[0])) == NULL)
        return ERROR;
    if (is_absolute_path(*path) == SUCCESS) {
        if (access(to_exec->args[0], F_OK) == 0)
            return SUCCESS;
        return FAILURE;
    }
    if ((env_path = get_all_path(mysh)) == NULL)
        return ERROR;
    if ((all_prefix = my_str_to_word_array(env_path, ":\0")) == NULL)
        return ERROR;
    res_all_try = try_all_paths(all_prefix, path);
    free_array(all_prefix);
    return res_all_try;
}
