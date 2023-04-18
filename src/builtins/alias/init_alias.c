/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include "mysh.h"
#include "str_func.h"
#include "alias.h"
#include "macro_errors.h"

int init_alias(mysh_t *mysh)
{
    struct stat file;
    mysh->alias.fd_alias_file = open(ALIASRC_FILE, O_CREAT |
    O_APPEND | O_RDWR, S_IRWXU);
    mysh->alias.fd_file = fopen(ALIASRC_FILE, "a+");
    if (mysh->alias.fd_file == NULL)
        return ERROR;
    if (stat(ALIASRC_FILE, &file) == -1)
        return ERROR;
    if (file.st_size == 0) {
        mysh->alias.tab_file = NULL;
    } else {
        mysh->alias.tab_file = file_to_tab(ALIASRC_FILE);
        if (mysh->alias.tab_file == NULL)
            return ERROR;
    }
    return SUCCESS;
}

static int add_alias_rc(mysh_t *mysh, char *input)
{
    int l_tab = 0;

    if (mysh->alias.tab_file == NULL) {
        mysh->alias.tab_file = malloc(sizeof(char *) * 2);
        if (mysh->alias.tab_file == NULL)
            return ERROR;
        mysh->alias.tab_file[0] = input;
        mysh->alias.tab_file[1] = NULL;
        fprintf(mysh->alias.fd_file, "%s", mysh->alias.tab_file[0]);
    } else {
        if (add_elem_tab_alias(&mysh->alias, input) == ERROR)
            return ERROR;
        l_tab = length_tab(mysh->alias.tab_file);
        fprintf(mysh->alias.fd_file, "%s", mysh->alias.tab_file[l_tab - 1]);
    }
    fflush(mysh->alias.fd_file);
    return SUCCESS;
}

static int display_alias(mysh_t *mysh)
{
    int l_tab = length_tab(mysh->alias.tab_file) - 1;

    for (; l_tab >= 0; l_tab -= 1) {
        printf("%s", mysh->alias.tab_file[l_tab]);
    }
    return SUCCESS;
}

int do_alias(mysh_t *mysh, command_t to_exec)
{
    char *command = NULL;
    if (to_exec.command[1] == NULL) {
        return display_alias(mysh);
    } else {
        command = remake_input(to_exec.command);
        if (add_alias_rc(mysh, command) == ERROR) {
            mysh->last_status = 1;
            return ERROR;
        }
    }
    return SUCCESS;
}

char *clean_last_input(char *last_input, char **tab_alias)
{
    char *to_free = last_input;

    last_input = remake_command(tab_alias);
    last_input = my_strcat_dup(last_input, "\n");
    free(to_free);
    return last_input;
}
int is_alias(mysh_t *mysh, char **input)
{
    char **tab_alias = NULL;
    char *last_input = NULL;
    char *to_compare = NULL;
    char *tmp = (*input);

    if (mysh->alias.tab_file == NULL)
        return SUCCESS;
    for (int i = 0; mysh->alias.tab_file[i] != NULL; i += 1) {
        tab_alias = my_str_to_word_array_separator
        (mysh->alias.tab_file[i], " \n");
        if (tab_alias == NULL)
            return ERROR;
        to_compare = my_strcat_dup(tab_alias[1], "\n");
        if (strcmp(tmp, to_compare) == 0) {
            last_input = clean_last_input(last_input, tab_alias);
            (*input) = last_input;
        }
        free_array(tab_alias);
        free(to_compare);
    }
    return SUCCESS;
}
