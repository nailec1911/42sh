/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** globbins
*/

#include <glob.h>
#include <stdlib.h>
#include <string.h>
#include "globbins.h"
#include "str_func.h"
#include "macro_errors.h"

static int is_globbing(char *arg)
{
    int has_bracket = 0;

    for (int i = 0; arg[i]; i++) {
        char const ch = arg[i];
        if (ch == '*' || ch == '?')
            return 1;
        if (ch == '[' || ch == ']')
            has_bracket |= (ch == '[') ? 1 << 0 : 1 << 1;
    }
    return (has_bracket & 1 << 0) && (has_bracket & 1 << 1);
}

static int get_glob_data(char *buf, glob_t *out)
{
    int ret = glob(buf, 0, 0, out);

    if (ret != 0)
        return ERROR;
    return SUCCESS;
}

static int get_new_argv_size(command_t cmd)
{
    int sz = 0;
    glob_t glob_data = {0};

    for (int i = 0; cmd.args[i]; i++) {
        if (!is_globbing(cmd.args[i])) {
            sz++;
            continue;
        }
        if (get_glob_data(cmd.args[i], &glob_data) == ERROR)
            continue;
        sz += glob_data.gl_pathc;
        globfree(&glob_data);
    }
    return sz;
}

static char **get_glob_argv(command_t *cmd, int *size)
{
    glob_t results = {0};
    int new_argv_sz = get_new_argv_size(*cmd);
    char **new_argv = malloc(8 * (new_argv_sz + 1));
    if (!new_argv)
        return 0;

    for (int i = 0; cmd->args[i]; i++) {
        if (!is_globbing(cmd->args[i])) {
            new_argv[(*size)++] = strdup(cmd->args[i]);
            continue;
        }
        if (get_glob_data(cmd->args[i], &results) == ERROR)
            continue;
        for (size_t y = 0; y < results.gl_pathc; y++)
            new_argv[(*size)++] = strdup(results.gl_pathv[y]);
        globfree(&results);
    }
    new_argv[new_argv_sz] = 0;
    return new_argv;
}

int update_glob_argv(and_command_t *cmd)
{
    int size = 0;
    command_t *cur_cmd = 0;
    char **new_argv = 0;

    for (int i = 0; i < cmd->nb_command; i += 1) {
        cur_cmd = &(cmd->tab_command[i]);
        new_argv = get_glob_argv(cur_cmd, &size);
        if (!new_argv)
            continue;
        free_array(cur_cmd->args);
        cur_cmd->args= new_argv;
        cur_cmd->nb_command = size;
        size = 0;
    }
    return SUCCESS;
}
