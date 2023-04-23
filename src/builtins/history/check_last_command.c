/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include "mysh.h"
#include <unistd.h>
#include "macro_errors.h"
#include "history.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "str_func.h"

void write_in_file(tab_hist_t **tab, FILE *fd)
{
    for (int i = 0; tab[i] != NULL; i += 1) {
        fprintf(fd, "%s  %s   %s", tab[i]->num, tab[i]->time, tab[i]->command);
    }
}

int replace_last_line(mysh_t *mysh, char *input)
{
    int l_tab = length_tab_hist(mysh->history.tab_hist);
    free(mysh->history.tab_hist[l_tab - 1]->num);
    free(mysh->history.tab_hist[l_tab - 1]->time);
    free(mysh->history.tab_hist[l_tab - 1]->command);
    mysh->history.tab_hist[l_tab - 1]->num =
    num_to_str(mysh->history.num_command);
    mysh->history.tab_hist[l_tab - 1]->time = create_time_line();
    mysh->history.tab_hist[l_tab - 1]->command = strdup(input);
    write_in_file(mysh->history.tab_hist, mysh->history.fd_file);
    return SUCCESS;
}

int add_line(mysh_t *mysh, char *input)
{
    if (add_elem_tab(&(mysh->history), input,
    mysh->history.num_command) == ERROR)
        return ERROR;
    write_in_file(mysh->history.tab_hist, mysh->history.fd_file);
    return SUCCESS;
}

int add_line_history(mysh_t *mysh, char *input)
{
    int l_tab = length_tab_hist(mysh->history.tab_hist);
    if (strcmp(input,mysh->history.tab_hist[l_tab - 1]->command) == 0) {
        return replace_last_line(mysh, input);
    } else {
        return add_line(mysh, input);
    }
}

int check_last_command(mysh_t *mysh, char *input)
{
    if (mysh->history.tab_hist == NULL) {
        mysh->history.tab_hist = malloc(sizeof(tab_hist_t *) * 2);
        mysh->history.tab_hist[0] = malloc(sizeof(tab_hist_t));
        mysh->history.tab_hist[0]->num = num_to_str(mysh->history.num_command);
        mysh->history.tab_hist[0]->time = create_time_line();
        mysh->history.tab_hist[0]->command = strdup(input);
        mysh->history.tab_hist[1] = NULL;
        write_in_file(mysh->history.tab_hist, mysh->history.fd_file);
    } else {
        return add_line_history(mysh, input);
    }
    return SUCCESS;
}
