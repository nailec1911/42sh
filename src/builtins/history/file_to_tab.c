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

static char **fill_tab_from_file(FILE *stream, int nb_line)
{
    int i = 0;
    int last = 0;
    char **tab = NULL;
    char *line = NULL;
    size_t len = 0;

    if ((tab = calloc(nb_line + 1, sizeof(char *))) == NULL)
        return NULL;
    while (getline(&line, &len, stream) != -1) {
        last = i;
        if (strncmp(line, "alias ", 6) == 0) {
            tab[i] = strdup(line);
            i += 1;
        }
        if (i != last && tab[i - 1] == NULL)
            return NULL;
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
