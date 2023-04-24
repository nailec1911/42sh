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

int add_in_history(mysh_t *mysh, char *input)
{
    if (strcmp("history\n", input) == 0)
        return SUCCESS;
    if (ftruncate(mysh->history.fd_history_file, 0) == -1) {
        return ERROR;
    }
    if (check_last_command(mysh, input) == ERROR)
        return ERROR;
    mysh->history.num_command += 1;
    fflush(mysh->history.fd_file);
    return SUCCESS;
}

static int get_num_command(mysh_t *mysh)
{
    if (file_to_tab_hist(HISTORY_FILE, mysh) == ERROR)
        return ERROR;
    mysh->history.num_command += 1;
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
        mysh->history.tab_hist = NULL;
    } else {
        if (get_num_command(mysh) == ERROR)
            return ERROR;
    }
    return SUCCESS;
}

static int fill_tab_hist_from_file(FILE *stream, mysh_t *mysh, int *i)
{
    char *line = NULL;
    char **tab = NULL;
    char *command = NULL;
    size_t len = 0;

    while (getline(&line, &len, stream) != -1) {
        if ((tab = my_str_to_word_array_separator(line, " \n")) == NULL)
            return ERROR;
        mysh->history.tab_hist[*i] = malloc(sizeof(tab_hist_t));
        mysh->history.tab_hist[*i]->num = num_to_str(atoi(tab[0]));
        mysh->history.tab_hist[*i]->time = strdup(tab[1]);
        command = remake_command(tab);
        mysh->history.tab_hist[*i]->command = my_strcat_dup(command, "\n");
        mysh->history.num_command = atoi(tab[0]);
        free_array(tab);
        free(command);
        *i += 1;
    }
    free(line);
    return SUCCESS;
}

int file_to_tab_hist(char *filepath, mysh_t *mysh)
{
    FILE *stream;
    int i = 0;
    int nb_line = get_nb_line(filepath);

    if (nb_line == -1)
        return ERROR;
    if ((mysh->history.tab_hist =
    malloc(sizeof(tab_hist_t *) * (nb_line + 1))) == NULL)
        return ERROR;
    mysh->history.tab_hist[nb_line] = NULL;
    stream = fopen(filepath, "r");
    fill_tab_hist_from_file(stream, mysh, &i);
    fclose(stream);
    return SUCCESS;
}
