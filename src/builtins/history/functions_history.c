/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include "mysh.h"
#include <sys/types.h>
#include "history.h"
#include "macro_errors.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "str_func.h"
#include <sys/stat.h>
#include "init.h"
#include <time.h>
int file_to_tab_hist(char *filepath, history_t *history);

int add_in_history(history_t *history, char *input)
{
    if (strcmp("history\n", input) == 0)
        return SUCCESS;
    if (ftruncate(history->fd_history_file, 0) == -1) {
        return ERROR;
    }
    if (check_last_command(history, input) == ERROR)
        return ERROR;
    history->num_cmd += 1;
    fflush(history->fd_file);
    return SUCCESS;
}

static int get_num_command(history_t *history, char *path)
{
    if (file_to_tab_hist(path, history) == ERROR) {
        history->have_hist = false;
        printf("Wrong syntaxe : The history will not be saved during \
this session\n");
        return SUCCESS;
    }
    history->num_cmd += 1;
    history->len_tab_hist = length_tab_hist(history->tab_hist);
    return SUCCESS;
}

static char *set_all_fd(history_t *history, char **env)
{
    char *path = NULL;

    if ((path = get_path_home(HISTORY_FILE, env)) == NULL)
        return NULL;
    if ((history->fd_history_file = open(path, O_CREAT |
    O_APPEND | O_RDWR, S_IRWXU)) == -1)
        return NULL;
    if ((history->fd_file = fdopen(history->fd_history_file, "a+")) == NULL)
        return NULL;
    return path;
}

int init_history(history_t *history, char **env)
{
    char *path = NULL;
    struct stat file;
    history->num_cmd = 0;
    history->have_hist = true;
    if ((path = set_all_fd(history, env)) == NULL)
        return ERROR;
    if (stat(path, &file) == -1)
        return ERROR;
    if (file.st_size == 0) {
        history->num_cmd = 1;
        history->tab_hist = NULL;
    } else {
        if (get_num_command(history, path) == ERROR)
            return ERROR;
    }
    return SUCCESS;
}
