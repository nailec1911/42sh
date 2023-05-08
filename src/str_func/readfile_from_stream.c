/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** readfile_from_stream
*/

#include <stdio.h>
#include <stdlib.h>

char* read_file_from_stream(FILE* file)
{
    char* buffer = NULL;
    size_t size = 0;
    size_t bytes_read;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    buffer = (char*) malloc(size + 1);
    if (!buffer)
        return NULL;

    bytes_read = fread(buffer, 1, size, file);
    buffer[bytes_read - 1] = '\0';

    return buffer;
}
