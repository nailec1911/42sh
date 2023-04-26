/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** ctrl_functions
*/

#include <unistd.h>
#include <stdio.h>

void left_ctrl(int *index)
{
    int temp = *index;

    *index = 0;
    for (int i = 0; i < temp; i += 1)
        printf("\033[D");
}

void right_ctrl(int *index, int *length)
{
    int temp = *index;

    *index = *length;
    for (int i = temp; i < *length; i += 1)
        printf("\033[C");
}

void ctrl_functions(int *index, int *length, int ch)
{
    read(STDIN_FILENO, &ch, 1);
    read(STDIN_FILENO, &ch, 1);
    read(STDIN_FILENO, &ch, 1);
    switch (ch) {
        case 'D':
            left_ctrl(index);
            break;
        case 'C':
            right_ctrl(index, length);
    }
}
