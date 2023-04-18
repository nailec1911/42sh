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

    #define HISTORY_FILE "assets/42shhistory"

    typedef struct histroy_s {
        int num_command;
        char *command;
        int fd_history_file;
        FILE *fd_file;
        char **tab_file;
    }history_t;

void print_tab(char **tab);
int length_tab(char **tab);
int biggest_line(char const *str);
int next_index(char const *str, int i);
int nb_char(char const *str, int index);
int do_width(char *map, int width);
char *clean_str(char *input);
int get_line(char const *file);
int get_col(char const *file);
char **compare_char(char **map, int i, int j, int *count);
char **single_line(char **map);
char **add_elem_tab(char **tab, char *to_add);
char **my_str_to_word_array_separator(char *str, char *separator);
int get_nb_line(char *filepath);
char *num_to_str(int num);
char **file_to_tab(char *filepath);
char *remake_command(char **tab);
#endif /* !HISTORY_H_ */
