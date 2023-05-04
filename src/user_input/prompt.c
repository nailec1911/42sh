/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <pwd.h>
#include <unistd.h>
#include "macro_errors.h"
#include "str_func.h"
#include "mysh.h"
#include "builtins/env.h"

char **set_all_for_prompt(char **user, char **pwd, int *tab_l, mysh_t *mysh)
{
    struct passwd *info;
    char **tab = NULL;
    *user = get_env_var(mysh, "USER=");
    *pwd = get_env_var(mysh, "PWD=");
    if (*pwd == NULL)
        *pwd = getcwd(*pwd, 0);
    tab = my_str_to_word_array_separator(*pwd, "/");
    if (tab == NULL)
        return NULL;
    *tab_l = length_tab(tab);
    if (user == NULL) {
        info = getpwuid(getuid());
        *user = info->pw_name;
    }
    return tab;
}

int init_prompt(mysh_t *mysh)
{
    char *pwd = NULL;
    char *user = NULL;
    int tab_l = 0;
    char **tab = NULL;

    if (!isatty(mysh->shell_descriptor))
        return SUCCESS;
    if ((tab = set_all_for_prompt(&user, &pwd, &tab_l, mysh)) == NULL)
        return ERROR;
    if (mysh->last_status == 0) {
        printf("\33[37;01m%d\33[00m | \33[34;01m%s\33[00m | \
\33[32;01m%s\33[00m > ", mysh->last_status, tab[tab_l - 1], user);
    } else {
        printf("\33[31;01m%d\33[00m | \33[34;01m%s\33[00m | \
\33[32;01m%s\33[00m > ", mysh->last_status, tab[tab_l - 1], user);
    }
    fflush(stdout);
    free_array(tab);
    return SUCCESS;
}
