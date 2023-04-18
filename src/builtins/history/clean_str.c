/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <unistd.h>
#include <time.h>
#include "str_func.h"
#include <stdlib.h>
#include "mysh.h"
#include <string.h>

char *clean_str(char *input)
{
    char **tab = my_str_to_word_array_separator(input, " \n");
    char *final_input = strdup(tab[0]);
    if (tab[1] == NULL) {
        free_array(tab);
        return final_input;
    }
    int i = 1;
    for (; tab[i] != NULL; i += 1) {
        final_input = my_strcat_dup(final_input, " ");
        final_input = my_strcat_dup(final_input, tab[i]);
    }
    free_array(tab);
    return final_input;
}

char *remake_command(char **tab)
{
    if (length_tab(tab) < 3)
        return strdup(tab[1]);
    char *final_input = strdup(tab[2]);
    int i = 3;
    for (; tab[i] != NULL; i += 1) {
        final_input = my_strcat_dup(final_input, " ");
        final_input = my_strcat_dup(final_input, tab[i]);
    }
    return final_input;
}

char *create_line_history(mysh_t *mysh, char *input)
{
    time_t timestamp = time(NULL);
    char *time_str = ctime(&timestamp);
    char **tab_time = my_str_to_word_array_separator(time_str, " ");
    char **hours_tab = my_str_to_word_array_separator(tab_time[3], ":");
    char *num_command = num_to_str(mysh->history.num_command);
    char *num_line = my_strcat_dup(num_command, "  ");
    char *num_time = my_strcat_dup(num_line, hours_tab[0]);
    char *time_line = my_strcat_dup(num_time, ":");
    char *full_time = my_strcat_dup(time_line, hours_tab[1]);
    char *command = my_strcat_dup(full_time, "   ");
    char *final_line = my_strcat_dup(command, input);
    free_array(tab_time);
    free_array(hours_tab);
    free(num_command);
    free(num_line);
    free(num_time);
    free(full_time);
    free(time_line);
    free(command);
    return final_line;
}

char *clean_last_input(char *last_input, char **tab_alias)
{
    char *to_free = last_input;

    last_input = remake_command(tab_alias);
    last_input = my_strcat_dup(last_input, "\n");
    free(to_free);
    return last_input;
}
