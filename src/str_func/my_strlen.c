/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

int my_strlen(char *str)
{
    int len = 0;
    for (int i = 0; str[i] != '\n' && str[i] != '\0'; i += 1) {
        len += 1;
    }
    return len;
}
