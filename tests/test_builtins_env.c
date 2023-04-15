/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** test_builtins_env
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include "macro_errors.h"
#include "list_env.h"
#include "mysh.h"
char **init_mysh_env(char * const env[]);
int do_setenv(mysh_t *mysh, command_t to_exec);
int do_env(mysh_t *mysh, command_t to_exec);
int do_unsetenv(mysh_t *mysh, command_t to_exec);
int do_exit(mysh_t *mysh, command_t to_exec);

Test(env1, normal_env){
    cr_redirect_stdout();
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t args = {0};

    args.env = init_mysh_env(env);
    args.command = (char *[2]){"env"};
    command_t command = {0};
    command.command = (char *[2]){"env"};
    command.fd_out = STDOUT_FILENO;
    cr_assert_eq(do_env(&args, command), SUCCESS);
    cr_assert_stdout_eq_str("test=12AZ\nhello=world\n");
    cr_assert_eq(args.last_status, 0);
}

Test(env2, env_null){
    mysh_t args = {0};
    args.env = (char *[]){NULL};
    args.command = (char *[2]){"env"};
    command_t command = {0};
    command.command = (char *[2]){"env"};
    cr_assert_eq(do_env(&args, command), SUCCESS);
    cr_assert_eq(args.last_status, 0);
}

Test(env3, too_much_args){
    cr_redirect_stderr();
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[3]){"env", "hello"};
    args.last_status = 0;

    command_t command = {0};
    command.command = (char *[3]){"env", "hello"};

    cr_assert_eq(do_env(&args, command), SUCCESS);
    cr_assert_stderr_eq_str("env: ‘hello’: No such file or directory\n");
    cr_assert_eq(args.last_status, 127);
}

Test(setenv1, not_existing_var){
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[4]){"setenv", "wait", "what?"};

    command_t command = {0};
    command.command = (char *[4]){"setenv", "wait", "what?"};
    cr_assert_eq(do_setenv(&args, command), SUCCESS);
    cr_assert_str_eq(args.env[2], "wait=what?");
    cr_assert_null(args.env[3]);
}

Test(setenv2, modify_existing_var){
    char *env[4] = {"test=12AZ", "hello=world", "third=time"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[4]){"setenv", "hello", "itsme"};
    command_t command = {0};
    command.command = (char *[4]){"setenv", "hello", "itsme"};
    cr_assert_eq(do_setenv(&args, command), SUCCESS);
    cr_assert_str_eq(args.env[1], "hello=itsme");
}

Test(setenv3, modify_existing_var_no_value){
    char *env[4] = {"test=12AZ", "hello=world", "third=time"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[3]){"setenv", "hello"};

    command_t command = {0};
    command.command = (char *[3]){"setenv", "hello"};
    cr_assert_eq(do_setenv(&args, command), SUCCESS);
    cr_assert_str_eq(args.env[1], "hello=");
}

Test(setenv4, env_is_null){
    mysh_t args = {0};
    args.env = (char *[]){NULL};
    args.command = (char *[4]){"setenv", "wait", "what?"};

    command_t command = {0};
    command.command = (char *[4]){"setenv", "wait", "what?"};
    cr_assert_eq(do_setenv(&args, command), SUCCESS);
    cr_assert_str_eq(args.env[0], "wait=what?");
    cr_assert_null(args.env[1]);
}

Test(setenv5, non_alphanum_char){
    cr_redirect_stderr();
    char *env[4] = {"test=12AZ", "hello=world", "third=time"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[4]){"setenv", "hz;s,zd", "itsme"};

    command_t command = {0};
    command.command = (char *[4]){"setenv", "hz;s,zd", "itsme"};
    cr_assert_eq(do_setenv(&args, command), SUCCESS);
    cr_assert_stderr_eq_str("setenv: Variable name must contain alphanumeric characters.\n");
    cr_assert_eq(args.last_status, 1);
}

Test(setenv6, too_much_argument){
    cr_redirect_stderr();
    char *env[4] = {"test=12AZ", "hello=world", "third=time"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[4]){"setenv", "hello", "itsme", "hey"};

    command_t command = {0};
    command.command = (char *[4]){"setenv", "hello", "itsme", "hey"};
    cr_assert_eq(do_setenv(&args, command), SUCCESS);
    cr_assert_stderr_eq_str("setenv: Too many arguments.\n");
    cr_assert_eq(args.last_status, 1);
}

Test(setenv7, no_args){
    cr_redirect_stdout();
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[2]){"setenv"};

    command_t command = {0};
    command.command = (char *[2]){"setenv"};
    command.fd_out = STDOUT_FILENO;
    cr_assert_eq(do_setenv(&args, command), SUCCESS);
    cr_assert_stdout_eq_str ("test=12AZ\nhello=world\n");
    cr_assert_eq(args.last_status, 0);
}

Test(unsetenv1, single_existing_var){
    cr_redirect_stderr();
    char *env[4] = {"test=12AZ", "hello=world", "third=time"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[4]){"unsetenv", "hello"};

    command_t command = {0};
    command.command = (char *[4]){"unsetenv", "hello"};
    command.fd_out = STDOUT_FILENO;
    cr_assert_eq(do_unsetenv(&args, command), SUCCESS);
    cr_assert_str_eq(args.env[1], "third=time");
    cr_assert_null(args.env[2]);
    cr_assert_eq(args.last_status, 0);
}

Test(unsetenv2, unset_first_var){
    cr_redirect_stderr();
    char *env[4] = {"test=12AZ", "hello=world", "third=time"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[4]){"unsetenv", "test"};

    command_t command = {0};
    command.command = (char *[4]){"unsetenv", "test"};
    command.fd_out = STDOUT_FILENO;
    cr_assert_eq(do_unsetenv(&args, command), SUCCESS);

    cr_assert_str_eq(args.env[0], "hello=world");
    cr_assert_str_eq(args.env[1], "third=time");
    cr_assert_null(args.env[2]);
    cr_assert_eq(args.last_status, 0);
}

Test(unsetenv3, unset_multiple_existing_var){
    char *env[4] = {"test=12AZ", "hello=world", "third=time"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[4]){"unsetenv", "test", "third"};

    command_t command = {0};
    command.command = (char *[4]){"unsetenv", "test", "third"};
    command.fd_out = STDOUT_FILENO;
    cr_assert_eq(do_unsetenv(&args, command), SUCCESS);

    cr_assert_str_eq(args.env[0], "hello=world");
    cr_assert_null(args.env[1]);
    cr_assert_eq(args.last_status, 0);
}

Test(unsetenv4, unset_not_existing_var){
    char *env[4] = {"test=12AZ", "hello=world", "third=time"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[4]){"unsetenv", "dumb"};

    command_t command = {0};
    command.command = (char *[4]){"unsetenv", "dumb"};
    command.fd_out = STDOUT_FILENO;
    cr_assert_eq(do_unsetenv(&args, command), SUCCESS);

    cr_assert_str_eq(args.env[0], "test=12AZ");
    cr_assert_str_eq(args.env[1], "hello=world");
    cr_assert_str_eq(args.env[2], "third=time");
    cr_assert_null(args.env[3]);
    cr_assert_eq(args.last_status, 0);
}

Test(unsetenv5, no_arg){
    cr_redirect_stderr();
    char *env[4] = {"test=12AZ", "hello=world", "third=time"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[2]){"unsetenv"};

    command_t command = {0};
    command.command = (char *[2]){"unsetenv"};
    command.fd_out = STDOUT_FILENO;
    cr_assert_eq(do_unsetenv(&args, command), SUCCESS);

    cr_assert_stderr_eq_str("unsetenv: Too few arguments.\n");
    cr_assert_str_eq(args.env[0], "test=12AZ");
    cr_assert_str_eq(args.env[1], "hello=world");
    cr_assert_str_eq(args.env[2], "third=time");
    cr_assert_null(args.env[3]);
    cr_assert_eq(args.last_status, 1);
}

Test(unsetenv6, no_env){
    mysh_t args = {0};
    args.env = (char *[]){NULL};
    args.command = (char *[4]){"unsetenv", "test"};

    command_t command = {0};
    command.command = (char *[4]){"unsetenv", "test"};
    command.fd_out = STDOUT_FILENO;
    cr_assert_eq(do_unsetenv(&args, command), SUCCESS);

    cr_assert_null(args.env[0]);
    cr_assert_eq(args.last_status, 0);
}

Test(unsetenv7, longer_value_than_searched){
    char *env[4] = {"testaaaa=12AZ", "helloaaa=world", "thirdaaa=time"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[5]){"unsetenv", "hello", "third", "test"};

    command_t command = {0};
    command.command = (char *[5]){"unsetenv", "hello", "third", "test"};
    command.fd_out = STDOUT_FILENO;
    cr_assert_eq(do_unsetenv(&args, command), SUCCESS);

    cr_assert_str_eq(args.env[0], "testaaaa=12AZ");
    cr_assert_str_eq(args.env[1], "helloaaa=world");
    cr_assert_str_eq(args.env[2], "thirdaaa=time");
    cr_assert_null(args.env[3]);
    cr_assert_eq(args.last_status, 0);
}

Test(exit1, exit_standar){
    cr_redirect_stderr();
    mysh_t args = {0};
    args.command = (char *[2]){"exit"};
    args.last_status = 0;

    command_t command = {0};
    command.command = (char *[2]){"exit"};
    cr_assert_eq(do_exit(&args, command), EXIT);
    cr_assert_eq(args.last_status, 0);
}

Test(exit2, exit_to_many_args){
    cr_redirect_stderr();
    mysh_t args = {0};
    args.command = (char *[3]){"exit", "test"};
    args.last_status = 0;

    command_t command = {0};
    command.command = (char *[3]){"exit", "test"};
    cr_assert_eq(do_exit(&args, command), SUCCESS);
    cr_assert_stderr_eq_str ("exit: Expression Syntax.\n");
    cr_assert_eq(args.last_status, 1);
}
