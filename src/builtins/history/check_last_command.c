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

static void write_in_file(char **tab, FILE *fd)
{
    for (int i = 0; tab[i] != NULL; i += 1) {
        fprintf(fd, "%s", tab[i]);
    }
}

int replace_last_line(mysh_t *mysh, char *input)
{
    int l_tab = length_tab(mysh->history->tab_file);
    char *command = create_line_history(mysh, input);
    mysh->history->tab_file[l_tab - 1] = my_strcat_dup(command, "\n");
    write_in_file(mysh->history->tab_file, mysh->history->fd_file);
    return SUCCESS;
}

int add_line(mysh_t *mysh, char *input)
{
    char *command = create_line_history(mysh, input);
    command = my_strcat_dup(command, "\n");
    mysh->history->tab_file = add_elem_tab(mysh->history->tab_file, command);
    write_in_file(mysh->history->tab_file, mysh->history->fd_file);
    return SUCCESS;
}

int add_line_history(mysh_t *mysh, char *input)
{
    int l_tab = length_tab(mysh->history->tab_file);
    char **tab_cmd = my_str_to_word_array_separator
    (mysh->history->tab_file[l_tab - 1], " \n");
    input = clean_str(input);
    char *to_compare = remake_command(tab_cmd);
    if (strcmp(input, to_compare) == 0) {
        return replace_last_line(mysh, input);
    } else {
        return add_line(mysh, input);
    }
}

int check_last_command(mysh_t *mysh, char *input)
{
    if (mysh->history->tab_file == NULL) {
        input = clean_str(input);
        char *command = create_line_history(mysh, input);
        mysh->history->tab_file = malloc(sizeof(char *) * 2);
        mysh->history->tab_file[0] = my_strcat_dup(command, "\n");
        mysh->history->tab_file[1] = NULL;
        fprintf(mysh->history->fd_file, "%s", mysh->history->tab_file[0]);
    } else {
        add_line_history(mysh, input);
    }
    return SUCCESS;
}
