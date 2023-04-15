/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** test_env_list
*/


#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "macro_errors.h"
#include "list_env.h"
#include "mysh.h"
int modify_env_var(char *to_change, mysh_t *mysh, char *new_value);
char **init_mysh_env(char * const env[]);

Test(create_list_env1, standar_env){
    char *env[4] = {"test", "hello", "third"};
    char **new = init_mysh_env(env);
    int i = 0;

    for (; env[i] != NULL; i += 1) {
        cr_assert_str_eq(env[i], new[i]);
    }
    cr_assert_null(new[i]);
}

Test(create_list_env2, one_elt_env){
    char *env[2] = {"test"};
    char **new = init_mysh_env(env);

    cr_assert_str_eq(env[0], new[0]);
    cr_assert_null(new[1]);

    char *new_env[2] = {""};
    new = init_mysh_env(new_env);
    cr_assert_str_eq(new_env[0], new[0]);
    cr_assert_null(new[1]);
}

Test(create_list_env3, null_env){
    char *env[1] = {NULL};
    char **new = init_mysh_env(env);
    cr_assert_null(new[0]);
    char **env2 = NULL;
    new = init_mysh_env(env2);
    cr_assert_null(new[0]);
}

Test(modify_env_var1, modify_existing_var){
    char *env[4] = {"test=12AZ", "hello=world", "third=time"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[]){"setenv", "hello"};
    cr_assert_eq(modify_env_var("hello", &args, "itsme"), SUCCESS);
    cr_assert_str_eq(args.env[1], "hello=itsme");
}

Test(modify_env_var2, not_existing_var){
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t args = {0};
    args.env = init_mysh_env(env);
    args.command = (char *[]){"setenv", "wait"};
    cr_assert_eq(modify_env_var("wait", &args, "what?"), SUCCESS);
    cr_assert_str_eq(args.env[2], "wait=what?");
    cr_assert_null(args.env[3]);
}
