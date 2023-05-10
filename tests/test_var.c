/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** test_var
*/


#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "macro_errors.h"
#include "mysh.h"
char **recreate_args(char **args);
int do_setvar(mysh_t *mysh, command_t *to_exec);
int do_unsetvar(mysh_t *mysh, command_t *to_exec);

Test(setvar_recreate_args, one_arg_r){
    char *arg[4] = {"set", "-r", "a"};
    char **res = recreate_args(arg);

    cr_assert_str_eq(res[0], "set");
    cr_assert_str_eq(res[1], "-r");
    cr_assert_str_eq(res[2], "a");
    cr_assert_null(res[3]);
}

Test(setvar_recreate_args, one_arg_splited){
    char *arg[5] = {"set", "a", "=", "bbb"};
    char **res = recreate_args(arg);

    cr_assert_str_eq(res[0], "set");
    cr_assert_str_eq(res[1], "a=bbb");
    cr_assert_null(res[2]);
}

Test(setvar_recreate_args, multiple_arg_unsplit){
    char *arg[4] = {"set", "a=b", "b=c"};
    char **res = recreate_args(arg);

    cr_assert_str_eq(res[0], "set");
    cr_assert_str_eq(res[1], "a=b");
    cr_assert_str_eq(res[2], "b=c");
    cr_assert_null(res[3]);
}

Test(setvar_recreate_args, mix_all){
    char *arg[11] = {"set", "a=b", "b", "=", "c", "d", "=", "d", "c", "e=e"};
    char **res = recreate_args(arg);

    cr_assert_str_eq(res[0], "set");
    cr_assert_str_eq(res[1], "a=b");
    cr_assert_str_eq(res[2], "b=c");
    cr_assert_str_eq(res[3], "d=d");
    cr_assert_str_eq(res[4], "c");
    cr_assert_str_eq(res[5], "e=e");
    cr_assert_null(res[6]);
}

Test(setvar_recreate_args, multiple_unique){
    char *arg[11] = {"set", "a", "b", "c", "d", "e", "f", "g"};
    char **res = recreate_args(arg);

    cr_assert_str_eq(res[0], "set");
    cr_assert_str_eq(res[1], "a");
    cr_assert_str_eq(res[2], "b");
    cr_assert_str_eq(res[3], "c");
    cr_assert_str_eq(res[4], "d");
    cr_assert_str_eq(res[5], "e");
    cr_assert_str_eq(res[6], "f");
    cr_assert_str_eq(res[7], "g");
    cr_assert_null(res[8]);
}


Test(setvar_recreate_args, multiple_separated){
    char *arg[15] = {"set", "a", "=", "hele_ze", "b", "=", "hele_ze", "c", "=", "hele_ze", "d", "=", "hele_ze"};
    char **res = recreate_args(arg);

    cr_assert_str_eq(res[0], "set");
    cr_assert_str_eq(res[1], "a=hele_ze");
    cr_assert_str_eq(res[2], "b=hele_ze");
    cr_assert_str_eq(res[3], "c=hele_ze");
    cr_assert_str_eq(res[4], "d=hele_ze");
    cr_assert_null(res[5]);
}

Test(setvar_recreate_args, arg_null){
    char **res = recreate_args(NULL);

    cr_assert_null(res[0]);
}

Test(set_var, wrongly_named){
    cr_redirect_stderr();
    char *env[3] = {"PATH=tests", "hello=world"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = env;
    shell.vars = NULL;
    to_exec.args = (char *[5]){"set", "-r", "*asd45*"};
    shell.last_status = 0;

    cr_assert_eq(do_setvar(&shell, &to_exec), SUCCESS);
    cr_assert_eq(shell.last_status, 1);
    cr_assert_stderr_eq_str("set: Variable name must begin with a letter.\n");
}

Test(set_var, set_one_var_no_val){
    cr_redirect_stderr();
    char *env[3] = {"PATH=tests", "hello=world"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = env;
    shell.vars = NULL;
    to_exec.args = (char *[5]){"set", "a"};
    shell.last_status = 0;
    cr_expect_eq(do_setvar(&shell, &to_exec), SUCCESS);
    cr_assert_eq(shell.last_status, 0);
    cr_assert_str_eq(shell.vars->name, "a");
}

Test(set_var, set_multiple_var_no_val){
    cr_redirect_stderr();
    char *env[3] = {"PATH=tests", "hello=world"};
    mysh_t shell = {0};
    command_t to_exec = {0};
    shell.env = env;
    shell.vars = NULL;
    to_exec.args = (char *[6]){"set", "a", "=", "a", "hollo=ff", NULL};
    shell.last_status = 0;
    cr_expect_eq(do_setvar(&shell, &to_exec), SUCCESS);
    cr_assert_eq(shell.last_status, 0);
    cr_assert_str_eq(shell.vars->name, "a");
    cr_assert_str_eq(shell.vars->buffer, "a");
    shell.vars = shell.vars->next;
    cr_assert_str_eq(shell.vars->name, "hollo");
    cr_assert_str_eq(shell.vars->buffer, "ff");
}

Test(unset_var, unset_one_var_no_val){
    cr_redirect_stderr();
    char *env[3] = {"PATH=tests", "hello=world"};
    mysh_t shell = {0};
    command_t to_exec = {0};

    shell.env = env;
    shell.vars = NULL;
    to_exec.args = (char *[5]){"set", "a"};
    shell.last_status = 0;
    cr_expect_eq(do_setvar(&shell, &to_exec), SUCCESS);
    to_exec.args =(char *[5]){"unset", "a"};
    cr_assert_eq(do_unsetvar(&shell, &to_exec), SUCCESS);
    cr_assert_eq(shell.last_status, 0);
    cr_assert_null(shell.vars);
}

Test(unset_var, unset_multiple){
    cr_redirect_stderr();
    char *env[3] = {"PATH=tests", "hello=world"};
    mysh_t shell = {0};
    command_t to_exec = {0};

    shell.env = env;
    shell.vars = NULL;
    to_exec.args = (char *[10]){"set", "a", "b", "s=s", "c=c"};
    shell.last_status = 0;
    cr_expect_eq(do_setvar(&shell, &to_exec), SUCCESS);
    to_exec.args =(char *[5]){"unset", "b"};
    cr_assert_eq(do_unsetvar(&shell, &to_exec), SUCCESS);
    cr_assert_eq(shell.last_status, 0);
    cr_assert_str_eq(shell.vars->name, "a");

    to_exec.args =(char *[5]){"unset", "a"};
    cr_assert_eq(do_unsetvar(&shell, &to_exec), SUCCESS);
    cr_assert_eq(shell.last_status, 0);
    cr_assert_str_eq(shell.vars->name, "s");
    cr_assert_str_eq(shell.vars->buffer, "s");

    to_exec.args =(char *[5]){"unset", "c"};
    cr_assert_eq(do_unsetvar(&shell, &to_exec), SUCCESS);
    cr_assert_eq(shell.last_status, 0);
    cr_assert_str_eq(shell.vars->name, "s");
    cr_assert_str_eq(shell.vars->buffer, "s");
    cr_assert_null(shell.vars->next);
}


Test(unset_var, unset_readable_only){
    cr_redirect_stderr();
    char *env[3] = {"PATH=tests", "hello=world"};
    mysh_t shell = {0};
    command_t to_exec = {0};

    shell.env = env;
    shell.vars = NULL;
    to_exec.args = (char *[10]){"set", "-r", "b", "s=s", "c=c"};
    cr_expect_eq(do_setvar(&shell, &to_exec), SUCCESS);
    shell.last_status = 0;
    to_exec.args =(char *[5]){"unset"};
    cr_assert_eq(do_unsetvar(&shell, &to_exec), SUCCESS);
    to_exec.args =(char *[5]){"unset", "b"};
    cr_assert_eq(do_unsetvar(&shell, &to_exec), SUCCESS);
    cr_assert_eq(shell.last_status, 0);
    cr_assert_str_eq(shell.vars->name, "b");
    cr_assert_stderr_eq_str("unset: Too few arguments.\nunset: $b is read-only.\n");
}
