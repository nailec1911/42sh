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
        int length_word;
        int ind_space;
        bool display;
        char *path;
        char **names;
        int index;
        int max_size;
    } tab_t;

#endif /* !TAB_H_ */
