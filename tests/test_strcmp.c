/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** test_strcmp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "macro_errors.h"
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
int str_is_alphanum(char *str);

Test(my_strcmp_1, equal_str){
    cr_assert_eq(my_strcmp("test", "test"), 0);
    cr_assert_eq(my_strcmp("t", "t"), 0);
    cr_assert_eq(my_strcmp("", ""), 0);
    cr_assert_eq(my_strcmp("qsdfghjk_-(&456", "qsdfghjk_-(&456"), 0);
}

Test(my_strcmp_2, first_str_is_shorter){
    cr_assert_eq(my_strcmp("test", "test2"), -50);
}

Test(my_strcmp_3, first_str_is_longer){
    cr_assert_eq(my_strcmp("test2", "test"), 50);
}

Test(my_strcmp_3, null_str){
    cr_assert_eq(my_strcmp(NULL, "test"), 116);
    cr_assert_eq(my_strcmp("test", NULL), 116);
    cr_assert_eq(my_strcmp(NULL, NULL), 0);
}


Test(my_strncmp_1, equal_str){
    cr_assert_eq(my_strncmp("test", "test", 4), 0);
    cr_assert_eq(my_strncmp("tesccddct", "tests", 1), 0);
    cr_assert_eq(my_strncmp("dscsdc", "cdcscsd", 0), 0);
}

Test(my_strncmp_2, null_str){
    cr_assert_eq(my_strncmp(NULL, "test", 2), 116);
    cr_assert_eq(my_strncmp("test", NULL, 2), 116);
    cr_assert_eq(my_strncmp(NULL, NULL, 2), 0);
}

Test(my_strncmp_3, len_to_long){
    cr_assert_eq(my_strncmp("test", "test", 6), 0);
}

Test(my_strncmp4, different_before_len){
    cr_assert_eq(my_strncmp("texxx", "test", 5), 5);
    cr_assert_eq(my_strncmp("test", "texxxx", 5), -5);
}

Test(my_strncmp5, one_shorter){
    cr_assert_eq(my_strncmp("test", "testaaaa", 7), -97);
    cr_assert_eq(my_strncmp("testaaaaaa", "test", 7), 97);
}

Test(str_is_alphanum1, only_alphanum){
    cr_assert_eq(str_is_alphanum("fdsfds4564ds"), 0);
    cr_assert_eq(str_is_alphanum("s"), 0);
    cr_assert_eq(str_is_alphanum("SHDSDdsdsd4564"), 0);
}

Test(str_is_alphanum1, not_alpha_num){
    cr_assert_eq(str_is_alphanum("fssf."), 1);
    cr_assert_eq(str_is_alphanum("scdsc:"), 1);
    cr_assert_eq(str_is_alphanum("SHD]"), 1);
    cr_assert_eq(str_is_alphanum("SHD}"), 1);
}