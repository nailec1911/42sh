/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** tab_function
*/

#ifndef TAB_FUNCTION_H_
    #define TAB_FUNCTION_H_

    #include "mysh.h"

    char *find_in_env(char **env, char *name);
    void display_spaces_comp(mysh_t *mysh, int count, int *length);
    void get_name_max_size(mysh_t *mysh);
    int parse_line(mysh_t *mysh, char **line, int *length);
    char *find_in_env(char **env, char *name);
    void change_target_tab(mysh_t *mysh, int *index, int *length, char **line);

#endif /* !TAB_FUNCTION_H_ */
