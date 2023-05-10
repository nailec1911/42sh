/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** str_func
*/

#include <stdio.h>

#ifndef STR_FUNC_H_
    #define STR_FUNC_H_

    #include <stdbool.h>

    char *my_strcat_dup(char *dest, char *src);
    char *my_strcat_with_char(char *dest, char const *src, char c);
    int str_is_alphanum(char *str);
    void free_array(char **array);
    int is_in(char c, char *str);
    int my_strstrlen(char *const str[]);
    char *clean_last_input(char **tab_alias);
    char *remove_first_char(char *input);
    bool is_num_char(char *str, char c);
    char **my_str_to_word_array(char *str, char const *separator);
    int count_word(char const *str, char const *separator);
    char *read_file(const char *filename);
    char *read_file_from_stream(FILE *stream);

#endif /* !STR_FUNC_H_ */
