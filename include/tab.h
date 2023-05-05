/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** tab
*/

#ifndef TAB_H_
    #define TAB_H_

    #include <stdbool.h>

    typedef struct tab_s {
        char *current;
        char *temp;
        char *path;
        char **names;
        int length_word;
        int length_comp;
        int nb_lines;
        int ind_space;
        int count;
        int color;
        int index;
        int max_size;
        bool display;
    } tab_t;

#endif /* !TAB_H_ */
