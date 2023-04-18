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
#include <sys/stat.h>
#include <time.h>

int add_in_history(mysh_t *mysh, char *input)
{
    if (ftruncate(mysh->history->fd_history_file, 0) == -1) {
        return ERROR;
    }
    mysh->history->fd_file = fdopen(mysh->history->fd_history_file, "a+");
    if (check_last_command(mysh, input) == ERROR)
        return ERROR;
    mysh->history->num_command += 1;
    fflush(mysh->history->fd_file);
    return SUCCESS;
}

static char const *get_last_line(mysh_t *mysh)
{
    (void)mysh;
    mysh->history->tab_file = file_to_tab(HISTORY_FILE);
    if (mysh->history->tab_file == NULL)
        return NULL;
    int len_tab = length_tab(mysh->history->tab_file);
    return mysh->history->tab_file[len_tab - 1];
}

static int get_num_command(mysh_t *mysh)
{
    char const *line = get_last_line(mysh);
    if (line == NULL)
        return ERROR;
    char **tab_last = my_str_to_word_array_separator((char *)line, " \n");
    mysh->history->num_command = atoi(tab_last[0]);
    mysh->history->num_command += 1;
    return SUCCESS;
}

int init_history(mysh_t *mysh)
{
    struct stat file;
    mysh->history = malloc(sizeof(history_t));
    if (mysh->history == NULL)
        return ERROR;
    mysh->history->num_command = 0;
    mysh->history->fd_history_file = open(HISTORY_FILE, O_CREAT |
    O_APPEND | O_RDWR);
    if (stat(HISTORY_FILE, &file) == -1)
        return ERROR;
    if (file.st_size == 0) {
        mysh->history->num_command = 1;
        mysh->history->tab_file = NULL;
    } else {
        if (get_num_command(mysh) == ERROR)
            return ERROR;
    }
    return SUCCESS;
}
