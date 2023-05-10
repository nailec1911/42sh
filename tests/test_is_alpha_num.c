/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** test_strcmp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "macro_errors.h"
int str_is_alphanum(char *str);

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
