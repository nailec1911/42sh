/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "str_func.h"
#include "mysh.h"
#include "history.h"
#include "macro_errors.h"

int add_in_history(history_t *history, char *input)
{
    if (!history || !input)
        return ERROR;
    if (strcmp("history\n", input) == 0)
        return SUCCESS;
    if (history->fd_history_file != -1
    && ftruncate(history->fd_history_file, 0) == -1) {
        return ERROR;
    }
    if (check_last_command(history, input) == ERROR)
        return ERROR;
    history->num_cmd += 1;
    return SUCCESS;
}

static int get_num_command(history_t *history, char *path)
{
    if (!history || !path)
        return ERROR;
    if (file_to_tab_hist(path, history) == ERROR) {
        fprintf(stderr, "Wrong syntaxe : The history will not be saved "
        "during this session\n");
        return SUCCESS;
    }
    history->num_cmd += 1;
    history->len_tab_hist = my_strstrlen((char **)history->tab_hist);
    return SUCCESS;
}

static char *set_all_fd(history_t *history)
{
    char *path = NULL;

    if (!history)
        return NULL;
    if ((path = get_path_home(HISTORY_FILE)) == NULL)
        return NULL;
    if ((history->fd_history_file = open(path, O_CREAT |
    O_APPEND | O_RDWR, 0644)) == -1) {
        if (isatty(SHELL_DESCRIPTOR) != 0)
            fprintf(stderr, ".42shhistory could not be opened, "
            "history will not be saved for this session\n");
        return NULL;
    }
    return path;
}

static int set_default(history_t *history)
{
    if (!history)
        return ERROR;
    history->num_cmd = 0;
    history->fd_history_file = -1;
    history->tab_hist = NULL;
    history->len_tab_hist = 0;
    if (isatty(SHELL_DESCRIPTOR) == 0)
        return ERROR;
    return SUCCESS;
}

int init_history(history_t *history)
{
    char *path = NULL;
    struct stat file;

    if (set_default(history) != SUCCESS)
        return SUCCESS;
    if ((path = set_all_fd(history)) == NULL)
        return SUCCESS;
    if (stat(path, &file) == -1)
        return ERROR;
    if (file.st_size == 0) {
        history->num_cmd = 1;
        history->tab_hist = NULL;
    } else {
        if (get_num_command(history, path) == ERROR) {
            free(path);
            return ERROR;
        }
    }
    free(path);
    return SUCCESS;
}
