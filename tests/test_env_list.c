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
env_var_t *create_list_env(char * const env[]);
int modify_env_var(char *to_change, mysh_t *mysh, char *new_value);
char **set_new_env(env_var_t *env_list);

Test(create_list_env1, standar_env){
    char *env[4] = {"test", "hello", "third"};

    env_var_t *env_list = create_list_env(env);
    for (int i = 0; env[i] != NULL; i += 1) {
        cr_assert_str_eq(env[i], env_list->var);
        env_list = env_list->next;
    }
    cr_assert_null(env_list);
}

Test(create_list_env2, one_elt_env){
    char *env[2] = {"test"};
    env_var_t *env_list = create_list_env(env);

    cr_assert_str_eq(env[0], env_list->var);
    cr_assert_null(env_list->next);

    char *new_env[2] = {""};
    env_list = create_list_env(new_env);

    cr_assert_str_eq(new_env[0], env_list->var);
    cr_assert_null(env_list->next);
}

Test(create_list_env3, null_env){
    char *env[1] = {NULL};
    env_var_t *env_list = create_list_env(env);
    cr_assert_null(env_list);
    char **env2 = NULL;
    env_list = create_list_env(env2);
    cr_assert_null(env_list);
}

Test(modify_env_var1, modify_existing_var){
    char *env[4] = {"test=12AZ", "hello=world", "third=time"};
    mysh_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[]){"setenv", "hello"};
    cr_assert_eq(modify_env_var("hello", &args, "itsme"), SUCCESS);
    cr_assert_str_eq(args.list_env->next->var, "hello=itsme");
}

Test(modify_env_var2, not_existing_var){
    char *env[3] = {"test=12AZ", "hello=world"};
    mysh_t args = {0};
    args.list_env = create_list_env(env);
    args.command = (char *[]){"setenv", "wait"};
    cr_assert_eq(modify_env_var("wait", &args, "what?"), SUCCESS);
    cr_assert_str_eq(args.list_env->next->next->var, "wait=what?");
    cr_assert_null(args.list_env->next->next->next);
}

Test(set_new_env1, normal_env){
    env_var_t *list_env = create_list_env((char *[3]){"test=12AZ", "hello=world"});

    char **result = set_new_env(list_env);
    int i = 0;

    for (; list_env != NULL; i += 1) {
        cr_assert_str_eq(result[i], list_env->var);
        list_env = list_env->next;
    }
    cr_assert_null(list_env);
    cr_assert_null(result[i]);
}

Test(set_new_env2, null_env){
    env_var_t *list_env = NULL;

    char **result = set_new_env(list_env);

    cr_assert_null(list_env);
    cr_assert_null(result[0]);
}