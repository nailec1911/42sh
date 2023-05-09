/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** test_builtin_cd
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <string.h>
#include "macro_errors.h"
#include "mysh.h"
#include "builtins/cd.h"
#include "parser/ast.h"
char **init_mysh_env(char * const env[]);
int do_cd(mysh_t *mysh, command_t command);

Test(get_path_cd1, correct_path){
    char *env[3] = {"test=12AZ", "hello=world"};
    command_t to_exec = {0};
    mysh_t shell = {0};
    shell.env = init_mysh_env(env);
    to_exec.args = (char *[2]){"cd", "tests"};
    shell.last_status = 0;

    char *result = get_path_to_go(&shell, &to_exec);
    cr_assert_str_eq(result, "tests");
    cr_assert_eq(shell.last_status, 0);
}

Test(get_path_cd2, home_path){
    char *env[3] = {"test=12AZ", "HOME=/home/usr"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = init_mysh_env(env);
    to_exec.args = (char *[2]){"cd"};
    shell.last_status = 0;

    char *result = get_path_to_go(&shell, &to_exec);
    cr_assert_str_eq(result, "/home/usr");
    cr_assert_eq(shell.last_status, 0);
}

Test(get_path_cd3, home_path_wave){
    char *env[3] = {"test=12AZ", "HOME=/home/usr"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = init_mysh_env(env);
    to_exec.args = (char *[2]){"cd", "~/src"};
    shell.last_status = 0;

    char *result = get_path_to_go(&shell, &to_exec);
    cr_assert_str_eq(result, "/home/usr/src");
    cr_assert_eq(shell.last_status, 0);
}

Test(get_path_cd4, get_oldpwd){
    char *env[3] = {"test=12AZ", "OLDPWD=/src"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = init_mysh_env(env);
    to_exec.args = (char *[2]){"cd", "-"};
    shell.last_status = 0;

    char *result = get_path_to_go(&shell, &to_exec);
    cr_assert_str_eq(result, "/src");
    cr_assert_eq(shell.last_status, 0);
}

Test(get_path_cd4, oldpwd_not_set){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = init_mysh_env(env);
    to_exec.args = (char *[2]){"cd", "-"};
    shell.last_status = 0;

    char *result = get_path_to_go(&shell, &to_exec);
    cr_assert_stderr_eq_str(": No such file or directory.\n");
    cr_assert_null(result);
    cr_assert_eq(shell.last_status, 1);
}

Test(get_path_cd5, home_not_set){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = init_mysh_env(env);
    to_exec.args = (char *[2]){"cd"};
    shell.last_status = 0;

    char *result = get_path_to_go(&shell, &to_exec);
    cr_assert_stderr_eq_str("cd: No home directory.\n");
    cr_assert_null(result);
    cr_assert_eq(shell.last_status, 1);
}

Test(get_path_cd4, wrong_minishell){
    char *env[3] = {"test=12AZ"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = init_mysh_env(env);
    to_exec.args = (char *[2]){"cd", "-dsqdsq"};
    shell.last_status = 0;

    char *result = get_path_to_go(&shell, &to_exec);
    cr_assert_str_eq(result, "-dsqdsq");
    cr_assert_eq(shell.last_status, 0);
}

Test(cd_1, too_many_args){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t shell = {0};
    shell.env = init_mysh_env(env);
    shell.last_status = 0;

    command_t command = {0};
    command.args = (char *[3]){"cd", "tests", "too_many"};
    command.fd_out = STDOUT_FILENO;

    cr_assert_eq(do_cd(&shell, command), 0);
    cr_assert_stderr_eq_str("cd: Too many arguments.\n");
    cr_assert_eq(shell.last_status, 1);
}

Test(cd_2, no_oldpwd){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t shell = {0};
    shell.env = init_mysh_env(env);
    shell.last_status = 0;

    command_t command = {0};
    command.args = (char *[3]){"cd", "-"};
    command.fd_out = STDOUT_FILENO;

    cr_assert_eq(do_cd(&shell, command), 0);
    cr_assert_stderr_eq_str(": No such file or directory.\n");
    cr_assert_eq(shell.last_status, 1);
}

Test(cd_3, not_a_directory){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t shell = {0};
    shell.env = init_mysh_env(env);
    shell.last_status = 0;

    command_t command = {0};
    command.args = (char *[3]){"cd", "Makefile"};
    command.fd_out = STDOUT_FILENO;

    cr_assert_eq(do_cd(&shell, command), 0);
    cr_assert_stderr_eq_str("Makefile: Not a directory.\n");
    cr_assert_eq(shell.last_status, 1);
}

Test(cd_4, wrongly_named){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t shell = {0};
    shell.env = init_mysh_env(env);
    shell.last_status = 0;

    command_t command = {0};
    command.args = (char *[3]){"cd", "YMCA"};
    command.fd_out = STDOUT_FILENO;

    cr_assert_eq(do_cd(&shell, command), 0);

    cr_assert_stderr_eq_str("YMCA: No such file or directory.\n");
    cr_assert_eq(shell.last_status, 1);
}

Test(cd_5, working_cd){
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t shell = {0};
    shell.env = init_mysh_env(env);
    shell.last_status = 0;

    char *actual = NULL;
    actual = getcwd(actual, 0);
    int len = strlen(actual);

    command_t command = {0};
    command.args = (char *[3]){"cd", "tests"};
    command.fd_out = STDOUT_FILENO;

    cr_assert_eq(do_cd(&shell, command), 0);

    cr_assert_eq(shell.last_status, 0);

    char *new = NULL;
    new = getcwd(new, 0);
    cr_assert_str_eq("/tests", new + len);
}

Test(cd_6, working_cd){
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t shell = {0};
    shell.env = init_mysh_env(env);
    shell.last_status = 0;

    char *actual = NULL;
    actual = getcwd(actual, 0);
        command_t command = {0};
    command.args = (char *[3]){"cd", "tests"};
    command.fd_out = STDOUT_FILENO;

    cr_assert_eq(do_cd(&shell, command), 0);


    command.args = (char *[3]){"cd", "-"};
    cr_assert_eq(do_cd(&shell, command), 0);
    cr_assert_eq(shell.last_status, 0);

    char *new = NULL;
    new = getcwd(new, 0);
    cr_assert_str_eq(actual, new);
}
