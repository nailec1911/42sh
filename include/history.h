/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#ifndef HISTORY_H_
    #define HISTORY_H_

    #include <stdio.h>
    #include <stdint.h>

    #define FLAG_H 0b0000001
    #define FLAG_R 0b0000010
    #define FLAG_C 0b0000100
    #define NO_FLAG 0
    #define IS_FLAG(flag, to_search) (to_search & flag)

    #define HISTORY_FILE "/.cache/.42shhistory"
    typedef struct tab_hist_s {
        char *num;
        char *time;
        char *command;
    } tab_hist_t;

    typedef struct histroy_s {
        int num_cmd;
        int fd_history_file;
        int len_tab_hist;
        tab_hist_t **tab_hist;
        uint8_t flags;
    }history_t;


int get_nb_line(char *filepath);
int add_elem_tab(history_t *history, char *to_add, int num);
char *num_to_str(int num);
char **file_to_tab(char *filepath);
char *remake_command(char **tab);
char *create_time_line(void);
void write_in_file(tab_hist_t **tab, int fd);
void free_tab_hist(tab_hist_t **tab);
char *find_in_env(char **env, char *name);
char *get_path_home(char *filepath);
int display_history(tab_hist_t **tab, int fd, history_t *history);
int file_to_tab_hist(char *filepath, history_t *history);


#endif /* !HISTORY_H_ */
