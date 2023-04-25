/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#ifndef HISTORY_H_
    #define HISTORY_H_

    #include <stdio.h>
    #include "mysh.h"

    #define HISTORY_FILE ".42shhistory"
    typedef struct tab_hist_s {
        char *num;
        char *time;
        char *command;
    } tab_hist_t;

    typedef struct histroy_s {
        int num_command;
        char *command;
        int fd_history_file;
        FILE *fd_file;
        char **tab_file;
        tab_hist_t **tab_hist;
    }history_t;


void print_tab(char **tab);
int length_tab(char **tab);
char **my_str_to_word_array_separator(char *str, char *separator);
int get_nb_line(char *filepath);
int add_elem_tab(history_t *history, char *to_add, int num);
char *num_to_str(int num);
char **file_to_tab(char *filepath);
char *remake_command(char **tab);
char *create_time_line(void);
int length_tab_hist(tab_hist_t **tab);
void write_in_file(tab_hist_t **tab, FILE *fd);
void free_tab_hist(tab_hist_t **tab);

#endif /* !HISTORY_H_ */
