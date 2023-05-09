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
#include "parser/ast.h"
#include "str_func.h"
int get_path(mysh_t *mysh, char **path, command_t *to_exec);
char **init_mysh_env(char * const env[]);

Test(get_path1, existing_absolute){
    char *env[3] = {"PATH=tests", "hello=world"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = env;
    to_exec.args = (char *[2]){"./Makefile"};
    shell.last_status = 0;


    cr_assert_eq(get_path(&shell, &to_exec.path, &to_exec), SUCCESS);
    cr_assert_str_eq(to_exec.path, "./Makefile");
    cr_assert_eq(shell.last_status, 0);
}

Test(get_path2, not_existing_absolute){
    char *env[3] = {"PATH=tests", "hello=world"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = env;
    to_exec.args = (char *[2]){"./tests/yhaaa"};
    shell.last_status = 0;


    cr_assert_eq(get_path(&shell, &to_exec.path, &to_exec), FAILURE);
    cr_assert_str_eq(to_exec.path, "./tests/yhaaa");
    cr_assert_eq(shell.last_status, 0);
}

Test(get_path3, doesnt_exist){
    char *env[3] = {"PATH=tests", "hello=world"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = env;
    to_exec.args = (char *[2]){"yhaaa"};
    shell.last_status = 0;


    cr_assert_eq(get_path(&shell, &to_exec.path, &to_exec), FAILURE);
    cr_assert_str_eq(to_exec.path, "yhaaa");
    cr_assert_eq(shell.last_status, 0);
}

Test(get_path4, is_in_PATH){
    char *env[3] = {"PATH=tests", "hello=world"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = env;
    to_exec.args = (char *[2]){"hello_world"};
    shell.last_status = 0;

    cr_assert_eq(get_path(&shell, &to_exec.path, &to_exec), SUCCESS);
    cr_assert_str_eq(to_exec.path, "tests/hello_world");
    cr_assert_eq(shell.last_status, 0);
}

Test(get_path5, no_PATH_var_cmd_not_found){
    char *env[3] = {"NOT_PATH=tests", "hello=world"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = env;
    to_exec.args = (char *[2]){"hello_world"};
    shell.last_status = 0;

    cr_assert_eq(get_path(&shell, &to_exec.path, &to_exec), FAILURE);
    cr_assert_str_eq(to_exec.path, "hello_world");
    cr_assert_eq(shell.last_status, 0);
}

Test(get_path6, no_PATH_var_cmd_in_default){
    char *env[3] = {"NOT_PATH=tests", "hello=world"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = env;
    to_exec.args = (char *[2]){"ls"};
    shell.last_status = 0;

    cr_assert_eq(get_path(&shell, &to_exec.path, &to_exec), SUCCESS);
    cr_assert_eq(shell.last_status, 0);
}

Test(get_path7, null_args){
    char *env[3] = {"NOT_PATH=tests", "hello=world"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = env;
    to_exec.args = (char *[2]){"ls"};
    shell.last_status = 0;

    cr_assert_eq(get_path(NULL, &to_exec.path, &to_exec), ERROR);
    cr_assert_eq(get_path(&shell, NULL, &to_exec), ERROR);
    cr_assert_eq(get_path(&shell, &to_exec.path, NULL), ERROR);
    to_exec.args = NULL;
    cr_assert_eq(get_path(&shell, &to_exec.path, &to_exec), ERROR);
}
