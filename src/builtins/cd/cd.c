/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** cd
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "builtins/env.h"
#include "all_args.h"
#include "str_func.h"
#include "macro_errors.h"
char *get_path_to_go(all_args_t *all_args);

static int update_env_var(char *old_pwd, all_args_t *all_args)
{
    char *new_pwd = NULL;

    if ((new_pwd = getcwd(new_pwd, 0)) == NULL) {
        all_args->last_status = errno;
        return ERROR;
    }
    if (modify_env_var("OLDPWD", all_args, old_pwd) == ERROR)
        return ERROR;
    if (modify_env_var("PWD", all_args, new_pwd) == ERROR)
        return ERROR;
    free(new_pwd);
    free(old_pwd);
    return SUCCESS;
}

static void display_error_chdir(int error_code, char *path)
{
    if (error_code == 2) {
        my_putstr(path, 2);
        my_putstr(": No such file or directory.\n", 2);
        return;
    }
    if (error_code == 20) {
        my_putstr(path, 2);
        my_putstr(": Not a directory.\n", 2);
        return;
    }
    if (error_code == 13) {
        my_putstr(path, 2);
        my_putstr(": Permission denied.\n", 2);
        return;
    }
    perror(path);
    return;
}

int do_cd(all_args_t *all_args, command_t to_exec)
{
    char *path = get_path_to_go(all_args);
    char *old_pwd = NULL;
    (void)to_exec;
    if (all_args->command[1] != NULL && all_args->command[2] != NULL) {
        my_putstr("cd: Too many arguments.\n", 2);
        all_args->last_status = 1;
        return SUCCESS;
    }
    if (path == NULL)
        return SUCCESS;
    if ((old_pwd = getcwd(old_pwd, 0)) == NULL)
        return ERROR;
    if (chdir(path) == -1) {
        display_error_chdir(errno, all_args->command[1]);
        all_args->last_status = 1;
        free(old_pwd);
        return SUCCESS;
    }
    return update_env_var(old_pwd, all_args);
}
