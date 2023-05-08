/*
** EPITECH PROJECT, 2023
** Word split count
** File description:
** oui
*/

#include <stdlib.h>

static int skip_while(char const *str, int index)
{
    while (str[index + 1] != '\0' && str[index + 1] != ' ' &&
            str[index + 1] != '\t' && str[index + 1] != '\n') {
        index += 1;
    }
    return index;
}

int count_word(char const *str)
{
    if (str == NULL)
        return 0;

    int count = 0;

    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            count += 1;
            i = skip_while(str, i);
        }
    }
    return count;
}
