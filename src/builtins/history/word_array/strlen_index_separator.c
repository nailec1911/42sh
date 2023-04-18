/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
int loop_separator(char c, char *separator);

int my_strlen_index_separator(char *str, int index, char *separator)
{
    int lenght = 0;
    int i = index;
    for (; str[i] != '\n' && loop_separator(str[i],
    separator) == 1 && str[i] != '\0'; i += 1) {
            lenght += 1;
    }
    return lenght;
}
