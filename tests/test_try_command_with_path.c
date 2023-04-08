/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** test_try_command_with_path
*/


#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include "macro_errors.h"
#include "all_args.h"
#include "builtins/env.h"
#include "str_func.h"
int try_command_with_path(all_args_t *all_args);

Test(try_command1, command_not_found){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ", "hello=world"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[2]){"nevergonnagiveyouup"};
    args.last_status = 0;

    cr_assert_eq(try_command_with_path(&args), SUCCESS);
    cr_assert_stderr_eq_str("nevergonnagiveyouup: Command not found.\n");
    cr_assert_eq(args.last_status, 1);
}

Test(try_command2, hello_world){
    cr_redirect_stdout();
    char *actual = NULL;
    actual = getcwd(actual, 0);
    int len = my_strlen(actual);
    char *path_var = my_strcat_dup(actual, "/tests:");

    char *env[3] = {"test=12AZ", "hello=world"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[2]){"hello_world"};
    args.last_status = 0;

    modify_env_var("PATH", &args, path_var);

    cr_assert_eq(try_command_with_path(&args), SUCCESS);
    cr_assert_stdout_eq_str("hello world\n");
    cr_assert_eq(args.last_status, 0);
}