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
#include "mysh.h"
char *find_in_env(char **env, char *name);
void display_spaces_comp(mysh_t *mysh, int count, int *length);
void get_name_max_size(mysh_t *mysh);
void parse_line(mysh_t *mysh, char **line, int *length);
void change_target_tab(mysh_t *mysh, int *index, int *length, char **line);

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
    closedir(dir);
    return fill_tab_list(mysh, dir, ent, length);
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
        mysh->completion.display = true;
        get_name_max_size(mysh);
        display_completion(mysh, line, length);
    }
}
