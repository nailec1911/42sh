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

int init_prompt(mysh_t *mysh)
{
    struct passwd *info;
    int tab_l = 0;
    char **tab = NULL;
    char *user = get_env_var(mysh, "USER=");
    char *pwd = get_env_var(mysh, "PWD=");
    if (pwd == NULL)
        pwd = getcwd(pwd, 0);
    tab = my_str_to_word_array_separator(pwd, "/");
    if (tab == NULL)
        return ERROR;
    tab_l = length_tab(tab);
    if (user == NULL) {
        info = getpwuid(getuid());
        user = info->pw_name;
    }
    printf("\33[34;01m%s\33[00m | \33[32;01m%s\33[00m > ",
    tab[tab_l - 1], user);
    fflush(stdout);
    free_array(tab);
    return SUCCESS;
}
