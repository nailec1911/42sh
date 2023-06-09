/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mysh.h"
#include "history.h"
#include "macro_errors.h"
#include "str_func.h"

static int fill_tab(tab_hist_t **tab_hist, int i, char **tab)
{
    char *command = NULL;

    if ((tab_hist[i] = malloc(sizeof(tab_hist_t))) == NULL)
        return ERROR;
    if ((tab_hist[i]->num = num_to_str(atoi(tab[0]))) == NULL)
        return ERROR;
    if ((tab_hist[i]->time = strdup(tab[1])) == NULL)
        return ERROR;
    if ((command = remake_command(tab)) == NULL)
        return ERROR;
    if ((tab_hist[i]->command = my_strcat_dup(command, "\n")) == NULL)
        return ERROR;
    free(command);
    return SUCCESS;
}

static int check_syntaxe(char **tab)
{
    char **tab_time = NULL;
    if ((tab_time = my_str_to_word_array(tab[1], ":")) == NULL)
        return ERROR;
    if (my_strstrlen(tab_time) < 2 || !is_num_char(tab[0], ' ')) {
        free_array(tab_time);
        return ERROR;
    }
    if (!is_num_char(tab[1], ':')) {
        free_array(tab_time);
        return ERROR;
    }
    if ((atoi(tab_time[0]) < 0 || atoi(tab_time[0]) > 23) ||
    (atoi(tab_time[1]) < 0 || atoi(tab_time[1]) > 59))
        return ERROR;
    if (strlen(tab[1]) != 5) {
        free_array(tab_time);
        return ERROR;
    }
    free_array(tab_time);
    return SUCCESS;
}

static int check_and_fill_tab(char *line, int i, history_t *history)
{
    char **tab = NULL;

    if ((tab = my_str_to_word_array(line, " \n")) == NULL)
        return ERROR;
    if (my_strstrlen(tab) < 3) {
        free_array(tab);
        return FAILURE;
    }
    if (check_syntaxe(tab) == ERROR) {
        free_array(tab);
        return FAILURE;
    }
    if (fill_tab(history->tab_hist, i, tab) == ERROR) {
        free_array(tab);
        return ERROR;
    }
    history->num_cmd = atoi(tab[0]);
    free_array(tab);
    return SUCCESS;
}

static int fill_tab_hist_from_file(FILE *stream, history_t *history, int *i)
{
    char *line = NULL;
    size_t len = 0;
    int res = 0;

    if (!stream || !history || !i)
        return ERROR;
    while (getline(&line, &len, stream) != -1) {
        res = check_and_fill_tab(line, *i, history);
        if (res == ERROR) {
            free(line);
            return ERROR;
        } else {
            res == SUCCESS ? *i += 1 : *i;
        }
    }
    free(line);
    return SUCCESS;
}

int file_to_tab_hist(char *filepath, history_t *history)
{
    FILE *stream;
    int i = 0;
    int nb_line = get_nb_line(filepath);

    if (nb_line == -1)
        return ERROR;
    if ((history->tab_hist =
    calloc(nb_line + 1, sizeof(tab_hist_t *))) == NULL)
        return ERROR;
    history->tab_hist[nb_line] = NULL;
    if ((stream = fopen(filepath, "r")) == NULL)
        return ERROR;
    if (fill_tab_hist_from_file(stream, history, &i) == ERROR) {
        free(history->tab_hist);
        history->tab_hist = NULL;
        return ERROR;
    }
    fclose(stream);
    return SUCCESS;
}
