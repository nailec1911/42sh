/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** globbins
*/

#include <glob.h>
#include <string.h>
#include "globbins.h"
#include "str_func.h"
#include "macro_errors.h"

/*moove somewhere else?*/
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
    for (int i = 0; cmd.command[i]; i++) {
        if (!is_globbing(cmd.command[i])) {
            sz++;
            continue;
        }

        glob_t glob_data = {0};
        if (get_glob_data(cmd.command[i], &glob_data) == ERROR)
            continue;

        sz += glob_data.gl_pathc;
        globfree(&glob_data);
    }

    return sz;
}

static char **get_glob_argv(command_t *cmd, int *size)
{
    glob_t results = {0};
    char **new_argv = malloc(8 * (get_new_argv_size(*cmd) + 1));
    if (!new_argv)
        return 0;

    for (int i = 0; cmd->command[i]; i++) {
        if (!is_globbing(cmd->command[i])) {
            new_argv[(*size)++] = strdup(cmd->command[i]);
            continue;
        }
        if (get_glob_data(cmd->command[i], &results) == ERROR)
            continue;
        for (int y = 0; y < results.gl_pathc; y++)
            new_argv[(*size)++] = strdup(results.gl_pathv[y]);
        globfree(&results);
    }
    new_argv[*size] = 0;
    return new_argv;
}

int update_glob_argv(and_command_t *cmd)
{
    for (int i = 0; i < cmd->nb_command; i += 1) {
        int size = 0;
        command_t *cur_cmd = &(cmd->tab_command[i]);
        char **new_argv = get_glob_argv(cur_cmd, &size);
        if (!new_argv)
            continue;

        free_array(cur_cmd->command);
        cur_cmd->command = new_argv;
        cur_cmd->nb_command = size;
    }

    return SUCCESS;
}
