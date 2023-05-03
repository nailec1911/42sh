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
void catch_cursor_postition(mysh_t *mysh, int *length);
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
    mysh->completion.names = malloc(sizeof(char *) * count + 1);
    return fill_tab_list(mysh, dir, ent, length);
}

static void parse_line(mysh_t *mysh, char **line, int *length)
{
    int ind = *length;
    int memo = 0;
    int index = 0;
    char *mid_line = NULL;
    for (; ind > 0 && (*line)[ind - 1] != ' ' &&
    (*line)[ind - 1] != '/'; ind -= 1);
    memo = ind;
    mysh->completion.ind_space = memo;
    for (; memo > 0 && (*line)[memo - 1] != ' '; memo -= 1);
    mid_line = malloc(sizeof(char) * (*length));
    for (; memo < ind; memo += 1) {
        mid_line[index] = (*line)[memo];
        index += 1;
    }
    mid_line[index] = '\0';
    mysh->completion.current =
    malloc(sizeof(char) * strlen(&((*line)[ind])) + 1);
    mysh->completion.current = strcpy(mysh->completion.current, &(*line)[ind]);
    mysh->completion.path = my_strcat_dup(find_in_env(mysh->env, "PWD="), "/");
    mysh->completion.path = my_strcat_dup(mysh->completion.path, mid_line);
}

void display_completion(mysh_t *mysh, char **line, int *length)
{
    int count = 0;
    mysh->completion.nb_lines = 0;
    mysh->completion.length_word =
    strlen(&(*line)[mysh->completion.ind_space]);

    for (int i = 0; mysh->completion.names[i] != NULL; i += 1) {
        if (count % 3 == 0) {
            printf("\n");
            mysh->completion.nb_lines += 1;
        }
        if (mysh->completion.index != i)
            printf("\033[0m%s\033[0m   ", mysh->completion.names[i]);
        else
            printf("\033[36;7m%s\033[0m   ", mysh->completion.names[i]);
        count += 1;
    }
    printf("\033[u");
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
        catch_cursor_postition(mysh, length);
        mysh->completion.display = true;
        display_completion(mysh, line, length);
    }
}
