/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#ifndef INIT_H_
    #define INIT_H_

    #include "mysh.h"
    #include "alias.h"
    #include "history.h"

    int add_in_history(mysh_t *mysh, char *input);
    int init_history(mysh_t *mysh);
    int get_num_command(mysh_t *mysh);

#endif /* !INIT_H_ */
