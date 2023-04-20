/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_input_line
*/

#include <unistd.h>
#include <stdio.h>

char *get_input_line(void)
{
    char *line = NULL;
    size_t len = 0;
    size_t nread = 0;

    while (nread == 0){
        nread = getline(&line, &len, stdin);
        if (nread == (size_t)-1){
            return NULL;
        }
    }
    return line;
}
