/*
** EPITECH PROJECT, 2023
** Word split count
** File description:
** oui
*/

#include <stdlib.h>
#include <stdbool.h>

static bool is_separator(char c, char const *separator)
{
    for (int i = 0; separator[i] != '\0'; i += 1) {
        if (separator[i] == c || c == '\0')
            return true;
    }
    return false;
}

static int skip_while(char const *str, int index, char const *separator)
{
    while (!is_separator(str[index + 1], separator)) {
        index += 1;
    }
    return index;
}

int count_word(char const *str, char const *separator)
{
    int count = 0;

    if (!str || !separator)
        return 0;
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (!is_separator(str[i], separator)) {
            count += 1;
            i = skip_while(str, i, separator);
        }
    }
    return count;
}
