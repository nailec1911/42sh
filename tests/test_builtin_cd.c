/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** test_builtin_cd
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include "macro_errors.h"
#include "list_env.h"
#include "all_args.h"
env_var_t *create_list_env(char * const env[]);
char *get_path_to_go(all_args_t *all_args);
int do_cd(all_args_t *all_args, command_t command);
char *get_env_var(env_var_t *list_env, char *var);
int my_strlen(char const *str);

Test(get_path_cd1, correct_path){
    char *env[3] = {"test=12AZ", "hello=world"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[2]){"cd", "tests"};
    args.last_status = 0;

    char *result = get_path_to_go(&args);
    cr_assert_str_eq(result, "tests");
    cr_assert_eq(args.last_status, 0);
}

Test(get_path_cd2, home_path){
    char *env[3] = {"test=12AZ", "HOME=/home/usr"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[2]){"cd"};
    args.last_status = 0;

    char *result = get_path_to_go(&args);
    cr_assert_str_eq(result, "/home/usr");
    cr_assert_eq(args.last_status, 0);
}

Test(get_path_cd3, home_path_wave){
    char *env[3] = {"test=12AZ", "HOME=/home/usr"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[2]){"cd", "~/src"};
    args.last_status = 0;

    char *result = get_path_to_go(&args);
    cr_assert_str_eq(result, "/home/usr/src");
    cr_assert_eq(args.last_status, 0);
}

Test(get_path_cd4, get_oldpwd){
    char *env[3] = {"test=12AZ", "OLDPWD=/src"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[2]){"cd", "-"};
    args.last_status = 0;

    char *result = get_path_to_go(&args);
    cr_assert_str_eq(result, "/src");
    cr_assert_eq(args.last_status, 0);
}

Test(get_path_cd4, oldpwd_not_set){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[2]){"cd", "-"};
    args.last_status = 0;

    char *result = get_path_to_go(&args);
    cr_assert_stderr_eq_str(": No such file or directory.\n");
    cr_assert_null(result);
    cr_assert_eq(args.last_status, 1);
}

Test(get_path_cd5, home_not_set){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[2]){"cd"};
    args.last_status = 0;

    char *result = get_path_to_go(&args);
    cr_assert_stderr_eq_str("cd: No home directory.\n");
    cr_assert_null(result);
    cr_assert_eq(args.last_status, 1);
}

Test(get_path_cd4, wrong_minishell){
    char *env[3] = {"test=12AZ"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[2]){"cd", "-dsqdsq"};
    args.last_status = 0;

    char *result = get_path_to_go(&args);
    cr_assert_str_eq(result, "-dsqdsq");
    cr_assert_eq(args.last_status, 0);
}

Test(cd_1, too_many_args){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ", "hello=world"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[3]){"cd", "tests", "too_many"};
    args.last_status = 0;

    command_t command = {0};
    command.command = (char *[3]){"cd", "tests", "too_many"};
    command.fd_out = STDOUT_FILENO;

    cr_assert_eq(do_cd(&args, command), 0);
    cr_assert_stderr_eq_str("cd: Too many arguments.\n");
    cr_assert_eq(args.last_status, 1);
}

Test(cd_2, no_oldpwd){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ", "hello=world"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[3]){"cd", "-"};
    args.last_status = 0;

    command_t command = {0};
    command.command = (char *[3]){"cd", "-"};
    command.fd_out = STDOUT_FILENO;

    cr_assert_eq(do_cd(&args, command), 0);
    cr_assert_stderr_eq_str(": No such file or directory.\n");
    cr_assert_eq(args.last_status, 1);
}

Test(cd_3, not_a_directory){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ", "hello=world"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[3]){"cd", "Makefile"};
    args.last_status = 0;

    command_t command = {0};
    command.command = (char *[3]){"cd", "Makefile"};
    command.fd_out = STDOUT_FILENO;

    cr_assert_eq(do_cd(&args, command), 0);
    cr_assert_stderr_eq_str("Makefile: Not a directory.\n");
    cr_assert_eq(args.last_status, 1);
}

Test(cd_4, wrongly_named){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ", "hello=world"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[3]){"cd", "YMCA"};
    args.last_status = 0;

    command_t command = {0};
    command.command = (char *[3]){"cd", "YMCA"};
    command.fd_out = STDOUT_FILENO;

    cr_assert_eq(do_cd(&args, command), 0);

    cr_assert_stderr_eq_str("YMCA: No such file or directory.\n");
    cr_assert_eq(args.last_status, 1);
}

Test(cd_5, working_cd){
    char *env[3] = {"test=12AZ", "hello=world"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[3]){"cd", "tests"};
    args.last_status = 0;

    char *actual = NULL;
    actual = getcwd(actual, 0);
    int len = my_strlen(actual);

    command_t command = {0};
    command.command = (char *[3]){"cd", "tests"};
    command.fd_out = STDOUT_FILENO;

    cr_assert_eq(do_cd(&args, command), 0);

    cr_assert_eq(args.last_status, 0);

    char *new = NULL;
    new = getcwd(new, 0);
    cr_assert_str_eq("/tests", new + len);
}

Test(cd_6, working_cd){
    char *env[3] = {"test=12AZ", "hello=world"};
    all_args_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[3]){"cd", "tests"};
    args.last_status = 0;

    char *actual = NULL;
    actual = getcwd(actual, 0);
        command_t command = {0};
    command.command = (char *[3]){"cd", "tests"};
    command.fd_out = STDOUT_FILENO;

    cr_assert_eq(do_cd(&args, command), 0);


    args.command = (char *[3]){"cd", "-"};
    command.command = (char *[3]){"cd", "-"};
    cr_assert_eq(do_cd(&args, command), 0);
    cr_assert_eq(args.last_status, 0);

    char *new = NULL;
    new = getcwd(new, 0);
    cr_assert_str_eq(actual, new);
}