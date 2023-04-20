/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#ifndef ALIAS_H_
    #define ALIAS_H_

    #include <stdio.h>

    #define ALIASRC_FILE ".42shrc"

    typedef struct alias_s {
        int fd_alias_file;
        FILE *fd_file;
        char **tab_file;
    }alias_t;

char *remake_input(char **tab);
int add_elem_tab_alias(alias_t *alias, char *to_add);
int display_alias(alias_t alias, int fd);
int display_specific_alias(alias_t alias, char *to_find, int fd);

#endif /* !ALIAS_H_ */
