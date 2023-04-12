/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** test_handle_input
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include "macro_errors.h"
#include "mysh.h"
#include "builtins/env.h"
int handle_input(mysh_t *mysh);

Test(handle_input1, builtin_exit){
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[2]){"exit"};
    args.last_status = 0;

    cr_assert_eq(handle_input(&args), EXIT);
    cr_assert_eq(args.last_status, 0);
}

Test(handle_input2, hello_world){
    cr_redirect_stdout();
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[2]){"./tests/hello_world"};
    args.last_status = 0;

    cr_assert_eq(handle_input(&args), SUCCESS);
    cr_assert_stdout_eq_str("hello world\n");
    cr_assert_eq(args.last_status, 0);
}


Test(handle_input3, seggfault){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[2]){"./tests/seggfault"};
    args.last_status = 0;

    cr_assert_eq(handle_input(&args), SUCCESS);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
    cr_assert_eq(args.last_status, 139);
}