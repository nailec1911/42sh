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
#include <time.h>

static int just_history(char *input)
{
    char **tab_history = my_str_to_word_array_separator(input, " \n");
    if (tab_history == NULL)
        return ERROR;
    for (int i = 0; tab_history[i] != NULL; i += 1) {
        if (strcmp("history", tab_history[i]) == 0 &&
         tab_history[i + 1] == NULL) {
            free_array(tab_history);
            return EXIT;
        }
    }
    free_array(tab_history);
    return SUCCESS;
}

int add_in_history(mysh_t *mysh, char *input)
{
    int res = just_history(input);

    if (res == EXIT)
        return SUCCESS;
    if (res == ERROR)
        return ERROR;
    if (ftruncate(mysh->history.fd_history_file, 0) == -1) {
        return ERROR;
    }
    if (check_last_command(mysh, input) == ERROR)
        return ERROR;
    mysh->history.num_command += 1;
    fflush(mysh->history.fd_file);
    return SUCCESS;
}

static char *get_last_line(mysh_t *mysh)
{
    int len_tab = 0;

    mysh->history.tab_file = file_to_tab(HISTORY_FILE);
    if (mysh->history.tab_file == NULL)
        return NULL;
    len_tab = length_tab(mysh->history.tab_file);
    return mysh->history.tab_file[len_tab - 1];
}

static int get_num_command(mysh_t *mysh)
{
    char *line = get_last_line(mysh);
    if (line == NULL)
        return ERROR;
    char **tab_last = my_str_to_word_array_separator(line, " \n");
    mysh->history.num_command = atoi(tab_last[0]);
    mysh->history.num_command += 1;
    free_array(tab_last);
    return SUCCESS;
}

int init_history(mysh_t *mysh)
{
    struct stat file;
    mysh->history.num_command = 0;
    mysh->history.fd_history_file = open(HISTORY_FILE, O_CREAT |
    O_APPEND | O_RDWR, S_IRWXU);
    mysh->history.fd_file = fdopen(mysh->history.fd_history_file, "a+");
    if (stat(HISTORY_FILE, &file) == -1)
        return ERROR;
    if (file.st_size == 0) {
        mysh->history.num_command = 1;
        mysh->history.tab_file = NULL;
    } else {
        if (get_num_command(mysh) == ERROR)
            return ERROR;
    }
    return SUCCESS;
}
