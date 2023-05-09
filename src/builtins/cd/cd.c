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
#include <stdio.h>
#include "builtins/env.h"
#include "mysh.h"
#include "str_func.h"
#include "macro_errors.h"
#include "builtins/cd.h"

static int update_env_var(char *old_pwd, mysh_t *mysh)
{
    char *new_pwd = NULL;

    if ((new_pwd = getcwd(new_pwd, 0)) == NULL) {
        mysh->last_status = errno;
        return ERROR;
    }
    if (modify_env_var("OLDPWD", mysh, old_pwd) == ERROR)
        return ERROR;
    if (modify_env_var("PWD", mysh, new_pwd) == ERROR)
        return ERROR;
    free(new_pwd);
    free(old_pwd);
    return SUCCESS;
}

static void display_error_chdir(int error_code, char *path)
{
    if (error_code == 2) {
        fprintf(stderr, "%s: No such file or directory.\n", path);
        return;
    }
    if (error_code == 20) {
        fprintf(stderr, "%s: Not a directory.\n", path);
        return;
    }
    if (error_code == 13) {
        fprintf(stderr, "%s: Permission denied.\n", path);
        return;
    }
    perror(path);
    return;
}

static int go_to_new_dir(mysh_t *mysh, char *path, char *name)
{
    char *old_pwd = NULL;

    if ((old_pwd = getcwd(old_pwd, 0)) == NULL)
        return ERROR;
    if (chdir(path) == -1) {
        display_error_chdir(errno, name);
        mysh->last_status = 1;
        free(old_pwd);
        return SUCCESS;
    }
    return update_env_var(old_pwd, mysh);
}

int do_cd(mysh_t *mysh, command_t to_exec)
{
    char *path = NULL;

    if (!mysh)
        return ERROR;
    if (to_exec.args[1] != NULL && to_exec.args[2] != NULL) {
        fprintf(stderr, "cd: Too many arguments.\n");
        mysh->last_status = 1;
        return SUCCESS;
    }
    path = get_path_to_go(mysh, &to_exec);
    if (path == NULL)
        return SUCCESS;
    return go_to_new_dir(mysh, path, to_exec.args[1]);
}
