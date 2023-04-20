/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** parsing_history_spe
*/

#include <unistd.h>
#include <string.h>
#include "str_func.h"

char *parsing_history_spe(char *line, char *str, int *length)
{
    int count = 0;
    int i = 0;

    for (int k = 0; k < *length; k += 1)
        line[k] = '\0';
    for (; str[i] != '\0' && str[i] != '\n'; i += 1) {
        if (char_isnum(str[i]) == 0 && str[i + 1] == ' ')
            count += 1;
        if (count == 2)
            break;
    }
    i += 4;
    count = 0;
    for (; str[i] != '\n' && str[i] != '\0'; i += 1) {
        line[count] = str[i];
        count += 1;
    }
    line[count] = '\0';
    return line;
}
