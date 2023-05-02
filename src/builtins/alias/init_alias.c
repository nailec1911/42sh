/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include "mysh.h"
#include "str_func.h"
#include "alias.h"
#include "macro_errors.h"

static char *set_all_fd(alias_t *alias, char **env)
{
    char *path = NULL;
    alias->have_alias = true;

    if ((path = get_path_home(ALIASRC_FILE, env)) == NULL)
        return NULL;
    alias->fd_alias_file = open(path, O_CREAT |
    O_APPEND | O_RDWR, S_IRWXU);
    if ((alias->fd_file = fopen(path, "a+")) == NULL)
        return NULL;
    return path;
}

int init_alias(alias_t *alias, char **env)
{
    char *path = NULL;
    struct stat file;

    if ((path = set_all_fd(alias, env)) == NULL)
        return ERROR;
    if (stat(path, &file) == -1)
        return ERROR;
    if (file.st_size == 0)
        alias->tab_file = NULL;
    else {
        if ((alias->tab_file = file_to_tab(path)) == NULL) {
            alias->have_alias = false;
            return SUCCESS;
        }
    }
    free(path);
    return SUCCESS;
}
