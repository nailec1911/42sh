/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-bsminishell1-celian.lombardot
** File description:
** my_putstr
*/

#include <unistd.h>
int my_strlen(char const *str);

void my_putstr(char *str, int output)
{
    int len = my_strlen(str);

    write(output, str, len);
}
