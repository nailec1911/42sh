/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#ifndef ALIAS_H_
    #define ALIAS_H_

    #include <stdio.h>

    #define ALIASRC_FILE "assets/42shrc"

    typedef struct alias_s {
        int fd_alias_file;
        FILE *fd_file;
        char **tab_file;
    }alias_t;

char *remake_input(char **tab);

#endif /* !ALIAS_H_ */
