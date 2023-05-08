/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <string.h>
#include "macro_errors.h"
#include "str_func.h"
#include <unistd.h>
#include <pwd.h>

char *get_path_home(char *filepath)
{
    char *home = NULL;
    struct passwd *pwd;

    pwd = getpwuid(getuid());
    if (!pwd)
        return NULL;
    home = my_strcat_dup(pwd->pw_dir, filepath);
    return home;
}
