/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** str_func
*/

#ifndef STR_FUNC_H_
    #define STR_FUNC_H_

    #include <stdbool.h>

    char **input_to_array(char const *str, char *separator);
    char *my_strcat_dup(char *dest, char *src);
    char *my_strcat_with_char(char *dest, char const *src, char c);
    int my_strcmp(char const *s1, char const *s2);
    int my_strncmp(char const *s1, char const *s2, int n);
    int str_is_alphanum(char *str);
    int char_isnum(char c);
    void free_array(char **array);
    int is_in(char c, char *str);
    int my_strstrlen(char *str[]);
    char *clean_last_input(char **tab_alias);
    bool is_num(char *str);
    int my_strlen(char *str);
    char *remove_first_char(char *input);
    bool is_num_space(char *str);
    bool is_num_colon(char *str);
    char **my_str_to_word_array(char *str);
    int count_word(char const *str);


#endif /* !STR_FUNC_H_ */
