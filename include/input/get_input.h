/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** get_input
*/

#ifndef GET_INPUT_H_
    #define GET_INPUT_H_

    #include <termios.h>
    #include "mysh.h"

    int arrow_function(int *index, int *length, char **line, mysh_t *mysh);
    void right_arrow_function(int *index, int length);
    void left_arrow_function(int *index);
    char *ctrl_d_function(mysh_t *mysh);
    void manage_enter_function(mysh_t *mysh);
    void manage_tab_function
    (int *length, int *index, char **line, mysh_t *mysh);
    void set_terminal
    (struct termios *o_term, struct termios *term, mysh_t *mysh);
    void backward_function(mysh_t *mysh, int *length, int *index, char **line);
    char *remove_char(char *line, int index, int length);
    char *suppr_function(int *index, int *length, char *line);
    void choose_arrow(mysh_t *mysh, int *index, int *length, char **line);

#endif /* !GET_INPUT_H_ */
