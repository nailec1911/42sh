/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** str_func
*/

#ifndef STR_FUNC_H_
    #define STR_FUNC_H_

    char **input_to_array(char const *str, char *separator);
    char *my_strcat_dup(char *dest, char *src);
    char *my_strcat_with_char(char *dest, char const *src, char c);
    int my_strcmp(char const *s1, char const *s2);
    int my_strncmp(char const *s1, char const *s2, int n);
    int str_is_alphanum(char *str);
    void free_array(char **array);
    int is_in(char c, char *str);
    int my_strstrlen(char *str[]);

#endif /* !STR_FUNC_H_ */
