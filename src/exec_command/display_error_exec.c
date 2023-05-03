/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** display_error_exec
*/

#include <stdio.h>

void display_error_exec(int error_code, char *path)
{
    switch (error_code) {
        case (2):
            fprintf(stderr, "%s: Command not found\n", path);
            break;
        case (8):
            fprintf(stderr,
                    "%s: Exec format error. Wrong Architecture.\n", path);
            break;
        case (20):
            fprintf(stderr, "%s: Not a directory.\n", path);
            break;
        case (13):
            fprintf(stderr, "%s: Permission denied.\n", path);
            break;
        default:
            perror(path);
    }
}
