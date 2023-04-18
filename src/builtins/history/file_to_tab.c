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
#include <string.h>

int count_line(char *str)
{
    int line = 0;
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == '\n')
            line += 1;
    }
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

char **file_to_tab(char *filepath)
{
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    int i = 0;
    int nb_line = get_nb_line(filepath);
    if (nb_line == -1)
        return NULL;
    stream = fopen(filepath, "r");
    char **tab = NULL;
    if ((tab = malloc(sizeof(char *) * (nb_line + 1))) == NULL)
        return NULL;
    tab[nb_line] = NULL;
    while ((nread = getline(&line, &len, stream)) != -1) {
        tab[i] = strdup(line);
        if (tab[i] == NULL)
            return NULL;
        i += 1;
    }
    return tab;
}
