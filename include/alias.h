/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#ifndef ALIAS_H_
    #define ALIAS_H_

    #include <stdio.h>
    #include <stdbool.h>

    #define ALIASRC_FILE "/.cache/.42shrc"

    typedef struct alias_s {
        int fd_alias_file;
        FILE *fd_file;
        char **tab_file;
        bool have_alias;
    }alias_t;

    char *remake_input(char **tab);
    int display_alias(char **tab_file, int fd);
    int display_specific_alias(char **tab_file, char *to_find, int fd);

#endif /* !ALIAS_H_ */
