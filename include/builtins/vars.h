/*
** EPITECH PROJECT, 2023
** tout ça
** File description:
** zzz
*/

#ifndef VARS_H
    #define VARS_H

    typedef struct vars_s {
        struct vars_s *next;
        struct vars_s *prev;
        char *name;
        char *buffer;
        char read_only;
    } vars_t;

    vars_t *create_global_var(char *buffer, char read_only);
    void add_global_var(vars_t **list, vars_t *new_var);
    vars_t *edit_global_var(vars_t *list, vars_t *new_var);
    vars_t *get_global_var_by_name(vars_t *list, char *name);
    void free_global_var(vars_t *var);
    char **recreate_args(char **args);

#endif /* !VARS_H */
