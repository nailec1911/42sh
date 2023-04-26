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

static int count_line(char *str)
{
    int line = 0;
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == '\n')
            line += 1;
    }
    free(str);
    return line;
}

int get_nb_line(char *filepath)
{
    struct stat file;
    char *str_file = NULL;

    int fd = open(filepath, O_RDONLY);
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
    if ((check = my_str_to_word_array_separator(line, " \n")) == NULL)
        return ERROR;
    if (length_tab(check) < 3) {
        free_array(check);
        return ERROR;
    }
    if (strcmp(check[0], "alias") != 0) {
        free_array(check);
        return ERROR;
    }
    free_array(check);
    return SUCCESS;
}

static char **fill_tab_from_file(FILE *stream, int nb_line)
{
    int i = 0;
    char **tab = NULL;
    char *line = NULL;
    size_t len = 0;

    if ((tab = malloc(sizeof(char *) * (nb_line + 1))) == NULL)
        return NULL;
    tab[nb_line] = NULL;
    while (getline(&line, &len, stream) != -1) {
        if (check_syntaxe(line) == ERROR) {
            free(line);
            return NULL;
        }
        tab[i] = strdup(line);
        if (tab[i] == NULL)
            return NULL;
        i += 1;
    }
    free(line);
    return tab;
}

char **file_to_tab(char *filepath)
{
    FILE *stream;
    int nb_line = get_nb_line(filepath);
    char **tab = NULL;

    if (nb_line == -1)
        return NULL;
    stream = fopen(filepath, "r");
    tab = fill_tab_from_file(stream, nb_line);
    fclose(stream);
    return tab;
}
