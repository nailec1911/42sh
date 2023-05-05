/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set_terminal
*/

#include <unistd.h>
#include <termios.h>
#include "mysh.h"

void set_terminal(struct termios *old_term, struct termios *term, mysh_t *mysh)
{
    tcgetattr(STDIN_FILENO, old_term);
    *term = *old_term;
    (*term).c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, term);
    mysh->tab = false;
}
