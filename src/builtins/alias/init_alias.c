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

static char *set_all_fd(alias_t *alias)
{
    char *path = NULL;

    path = get_path_home(ALIASRC_FILE);
    if (path == NULL)
        return NULL;
    if ((alias->fd_alias_file = open(path, O_CREAT |
    O_APPEND | O_RDWR, 0644)) == -1) {
        fprintf(stderr, ".42shrc failed to open, alias could not "
        "be loaded and will not be saved\n");
        return NULL;
    }
    return path;
}

static int set_alias_from_file(alias_t *alias, char *path)
{
    struct stat file;

    if (stat(path, &file) == -1)
        return ERROR;
    if (file.st_size == 0) {
        alias->tab_file = NULL;
    } else {
        alias->tab_file = file_to_tab(path);
        if (alias->tab_file == NULL) {
            free(path);
            return SUCCESS;
        }
    }
    free(path);
    return SUCCESS;
}

int init_alias(alias_t *alias)
{
    char *path = NULL;

    if (!alias)
        return ERROR;
    path = set_all_fd(alias);
    if (path == NULL) {
        alias->tab_file = NULL;
        return SUCCESS;
    }
    return set_alias_from_file(alias, path);
}
