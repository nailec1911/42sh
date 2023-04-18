/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** test_get_path
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <string.h>
#include "macro_errors.h"
#include "mysh.h"
#include "builtins/env.h"
#include "str_func.h"
int get_path(mysh_t *mysh, char **path);
char **init_mysh_env(char * const env[]);

Test(get_path1, existing_absolute){
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[2]){"./Makefile"};
    args.last_status = 0;

    char *path = NULL;

    cr_assert_eq(get_path(&args, &path), SUCCESS);
    cr_assert_str_eq(path, "./Makefile");
    cr_assert_eq(args.last_status, 0);
}

Test(get_path2, not_existing_absolute){
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[2]){"./tests/yhaaa"};
    args.last_status = 0;

    char *path = NULL;

    cr_assert_eq(get_path(&args, &path), FAILURE);
    cr_assert_str_eq(path, "./tests/yhaaa");
    cr_assert_eq(args.last_status, 0);
}

Test(get_path3, doesnt_exist){
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[2]){"yhaaa"};
    args.last_status = 0;

    char *path = NULL;

    cr_assert_eq(get_path(&args, &path), FAILURE);
    cr_assert_str_eq(path, "yhaaa");
    cr_assert_eq(args.last_status, 0);
}

Test(get_path4, is_in_PATH){
    char *actual = NULL;
    actual = getcwd(actual, 0);
    char *path_var = my_strcat_dup(actual, "/tests:");

    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[2]){"hello_world"};
    args.last_status = 0;

    modify_env_var("PATH", &args, path_var);
    char *path = NULL;
    char *result = strdup(get_env_var(&args, "PATH="));
    result[strlen(result) - 1] = '\0';
    result = my_strcat_with_char(result, "hello_world", '/');
    cr_assert_eq(get_path(&args, &path), SUCCESS);
    cr_assert_str_eq(path, result);
    cr_assert_eq(args.last_status, 0);
}
