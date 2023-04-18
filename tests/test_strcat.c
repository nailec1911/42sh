/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** test_str_function
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "macro_errors.h"
char *my_strcat_dup(char *dest, char *src);
char *my_strcat_with_char(char *dest, char const *src, char c);

Test(my_strcat_dup1, standard_case){
    char *result = my_strcat_dup("test", "after");

    cr_assert_str_eq(result, "testafter");
}

Test(my_strcat_dup2, second_null){
    char *result = my_strcat_dup("test", NULL);

    cr_assert_str_eq(result, "test");
}

Test(my_strcat_with_char1, standard_case){
    char *result = my_strcat_with_char("test", "next", '=');

    cr_assert_str_eq(result, "test=next");
}

Test(my_strcat_with_char1, second_is_null){
    char *result = my_strcat_with_char("test", NULL, '=');

    cr_assert_str_eq(result, "test=");
}
