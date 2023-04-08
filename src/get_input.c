/*
** EPITECH PROJECT, 2023
** B-PSU-100-BDX-1-1-navy-adam.de-lacheisserie-levy
** File description:
** input
*/

#include <stdio.h>
#include <unistd.h>

char *get_input(void)
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
