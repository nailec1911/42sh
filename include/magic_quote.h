/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** magic
*/

#ifndef MAGIC_H_
    #define MAGIC_H_

    #include <stdio.h>
    #include "mysh.h"

    FILE *get_file_res_command(mysh_t *mysh, char *quoted);
    int loop_sh(mysh_t *mysh, char *input);
    int set_new_tab(command_t *command, FILE *res, int ind);

#endif /* !MAGIC_H_ */
