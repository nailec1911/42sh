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

int init_alias(alias_t *alias)
{
    struct stat file;
    alias->fd_alias_file = open(ALIASRC_FILE, O_CREAT |
    O_APPEND | O_RDWR, S_IRWXU);
    alias->fd_file = fopen(ALIASRC_FILE, "a+");
    if (alias->fd_file == NULL)
        return ERROR;
    if (stat(ALIASRC_FILE, &file) == -1)
        return ERROR;
    if (file.st_size == 0) {
        alias->tab_file = NULL;
    } else {
        alias->tab_file = file_to_tab(ALIASRC_FILE);
        if (alias->tab_file == NULL) {
            printf("Wrong syntaxe : %s\n", ALIASRC_FILE);
            return ERROR;
        }
    }
    return SUCCESS;
}
