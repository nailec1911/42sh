/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** tab_function
*/

#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "str_func.h"
#include "macro_errors.h"
#include "input/tab_function.h"

static int fill_tab_list(mysh_t *mysh, DIR *dir, struct dirent *ent, int length)
{
    int index = 0;

    if ((dir = opendir(mysh->completion.path)) == NULL)
        return ERROR;
    while ((ent = readdir(dir)) != NULL)
        if (ent->d_name[0] != '.' &&
        strncmp(mysh->completion.current, ent->d_name, length) == 0) {
            mysh->completion.names[index] = strdup(ent->d_name);
            index += 1;
        }
    mysh->completion.names[index] = NULL;
    free(mysh->completion.current);
    free(mysh->completion.path);
    closedir(dir);
    return SUCCESS;
}

static int malloc_tab_list(mysh_t *mysh)
{
    DIR *dir;
    struct dirent *ent;
    int length = strlen(mysh->completion.current);
    int count = 0;

    if ((dir = opendir(mysh->completion.path)) == NULL)
        return ERROR;
    while ((ent = readdir(dir)) != NULL)
        if (strncmp(mysh->completion.current, ent->d_name, length) == 0)
            count += 1;
    mysh->completion.names = malloc(sizeof(char *) * (count + 1));
    return fill_tab_list(mysh, dir, ent, length);
}

static bool check_if_alone(mysh_t *mysh, char **line, int *length, int *index)
{
    int length_word = strlen(&(*line)[mysh->completion.ind_space]);

    if (length_tab(mysh->completion.names) > 1)
        return false;
    for (int i = mysh->completion.ind_space; i < *length; i += 1)
        printf("\033[D");
    printf("%s", mysh->completion.names[0]);
    for (int i = mysh->completion.ind_space; (*line)[i] != '\0'; i += 1)
        (*line)[i] = '\0';
    strcat(*line, mysh->completion.names[0]);
    *length += strlen(mysh->completion.names[0]) - length_word;
    *index = *length;
    return true;
}

void display_completion(mysh_t *mysh, char **line, int *length)
{
    int count = 0;

    mysh->completion.length_word =
    strlen(&(*line)[mysh->completion.ind_space]);
    display_spaces_comp(mysh, count, length);
    if (mysh->completion.length_comp < 0) {
        printf("\033[%dC", mysh->completion.length_comp * -1);
    } else {
        printf("\033[%dD", mysh->completion.length_comp);
    }
    printf("\033[%dA", mysh->completion.nb_lines);
    if (mysh->first_tab)
        for (int k = mysh->completion.ind_space; k < *length; k += 1)
            printf("\033[C");
}

void manage_tab_function(int *length, int *index, char **line, mysh_t *mysh)
{
    if (*line[0] == '\0') {
        mysh->tab = true;
        strcpy(*line, "ls");
        return;
    }
    if (mysh->completion.display) {
        mysh->first_tab = false;
        change_target_tab(mysh, index, length, line);
    } else {
        mysh->first_tab = true;
        parse_line(mysh, line, length);
        if (malloc_tab_list(mysh) == ERROR ||
        mysh->completion.names[0] == NULL)
            return;
        if (!check_if_alone(mysh, line, length, index)) {
            mysh->completion.display = true;
            get_name_max_size(mysh);
            display_completion(mysh, line, length);
        }
    }
}
