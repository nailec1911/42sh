/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** str_is_alphanum
*/

#include "macro_errors.h"

int str_is_alphanum(char *str)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] < '0' || ('9' < str[i] && str[i] < 'A')
        || ('Z' < str[i] && str[i] < 'a') || 'z' < str[i])
            return 1;
    }
    return SUCCESS;
}
