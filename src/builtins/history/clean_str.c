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
    int i = 1;
    char *temp = NULL;
    if (tab[1] == NULL) {
        free_array(tab);
        return final_input;
    }
    for (; tab[i] != NULL; i += 1) {
        temp = my_strcat_dup(final_input, " ");
        free(final_input);
        final_input = my_strcat_dup(temp, tab[i]);
        free(temp);
    }
    free_array(tab);
    return final_input;
}

char *remake_command(char **tab)
{
    char *final_input = NULL;
    char *temp = NULL;
    int i = 3;
    if (length_tab(tab) < 3) {
        return strdup(tab[1]);
    }
    final_input = strdup(tab[2]);
    for (; tab[i] != NULL; i += 1) {
        temp = my_strcat_dup(final_input, " ");
        free(final_input);
        final_input = my_strcat_dup(temp, tab[i]);
        free(temp);
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

char *clean_last_input(char **tab_alias)
{
    char *to_free = NULL;
    char *res = NULL;

    to_free = remake_command(tab_alias);
    res = my_strcat_dup(to_free, "\n");
    free(to_free);
    return res;
}
