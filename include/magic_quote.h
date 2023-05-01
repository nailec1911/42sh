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
    char **file_stream_to_tab(FILE *file);
    char **insert_array_in_array(char **to_insert, char **dest, int index);
    int loop_sh(mysh_t *mysh, char *input);

#endif /* !MAGIC_H_ */
