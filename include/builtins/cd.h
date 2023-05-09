/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** cd
*/


#ifndef cd_h_
    #define cd_h_

    #include "parser/ast.h"
    #include <mysh.h>
    int do_cd(mysh_t *mysh, command_t to_exec);
    char *get_path_to_go(mysh_t *mysh, command_t *to_exec);


#endif /* 42sh */
