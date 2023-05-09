/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include "macro_errors.h"
#include "mysh.h"
#include "sys/stat.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "history.h"
#include "str_func.h"
#include <string.h>
#include "init.h"

int get_nb_line(char *filepath)
{
    struct stat file;
    char *str_file = NULL;
    int fd = 0;

    if (!filepath)
        return ERROR;
    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        return -1;
    if (stat(filepath, &file) == -1)
        return -1;
    str_file = malloc(sizeof(char) * (file.st_size + 1));
    if (str_file == NULL)
        return -1;
    str_file[file.st_size] = '\0';
    read(fd, str_file, file.st_size);
    return count_line(str_file);
}

static int check_syntaxe(char *line)
{
    char **check = NULL;

    if (!line)
        return ERROR;
    if ((check = my_str_to_word_array_separator(line, " \n")) == NULL)
        return ERROR;
    if (length_tab(check) < 3) {
        free_array(check);
        return FAILURE;
    }
    if (strcmp(check[0], "alias") != 0) {
        free_array(check);
        return FAILURE;
    }
    free_array(check);
    return SUCCESS;
}

static int check_syntaxe_and_dup(char *line, char ***tab, int *i)
{
    int res = 0;
    if (!line || !tab || !i)
        return ERROR;
    if ((res = check_syntaxe(line)) != SUCCESS)
        return res;
    (*tab)[*i] = strdup(line);
    if ((*tab)[*i] == NULL)
        return ERROR;
    return SUCCESS;
}

static char **fill_tab_from_file(FILE *stream, int nb_line)
{
    int i = 0;
    char **tab = NULL;
    char *line = NULL;
    size_t len = 0;
    int res = 0;
    if (!stream)
        return NULL;
    if ((tab = calloc(nb_line + 1, sizeof(char *))) == NULL)
        return NULL;
    tab[nb_line] = NULL;
    while (getline(&line, &len, stream) != -1) {
        if ((res = check_syntaxe_and_dup(line, &tab, &i)) == ERROR) {
            free(line);
            free(tab);
            return NULL;
        } else
            res == SUCCESS ? i += 1 : i;
    }
    free(line);
    return tab;
}

char **file_to_tab(char *filepath)
{
    FILE *stream;
    int nb_line = 0;
    char **tab = NULL;

    if (filepath == NULL)
        return NULL;
    nb_line = get_nb_line(filepath);
    if (nb_line == -1)
        return NULL;
    if ((stream = fopen(filepath, "r")) == NULL)
        return NULL;
    tab = fill_tab_from_file(stream, nb_line);
    if (tab == NULL) {
        fprintf(stderr, "Wrong syntaxe : None alias will be saved "
        "during this session\n");
        return NULL;
    }
    fclose(stream);
    return tab;
}
