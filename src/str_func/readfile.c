/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    long file_size;
    char *file_content;
    if (!file)
        return NULL;

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    file_content = malloc(file_size + 1);
    if (!file_content)
        return NULL;

    fread(file_content, 1, file_size, file);
    fclose(file);
    file_content[file_size] = '\0';

    return file_content;
}
