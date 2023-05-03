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

    int add_in_history(history_t *history, char *input);
    int init_history(history_t *history);
    char *do_exclamation_mark(mysh_t *mysh, char *input);
    char *search_by_num(mysh_t *mysh, char *last_input);
    char *search_by_name(mysh_t *mysh, char *last_input);
    int file_to_tab_hist(char *filepath, history_t *history);


#endif /* !INIT_H_ */
