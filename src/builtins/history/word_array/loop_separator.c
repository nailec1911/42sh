/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

int loop_separator(char c, char *separator)
{
    for (int i = 0; separator[i] != '\0'; i += 1) {
        if (separator[i] == c) {
            return 0;
        }
    }
    return 1;
}
