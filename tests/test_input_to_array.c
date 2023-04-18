/*
** EPITECH PROJECT, 2023
** stumper
** File description:
** test_check_args
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include "macro_errors.h"
char **input_to_array(char const *str, char *separator);

Test(input_to_array_1, two_words){
    char **result = input_to_array("ls -l", " ");

    cr_assert_str_eq(result[0], "ls");
    cr_assert_str_eq(result[1], "-l");
    cr_assert_null(result[2]);
}

Test(input_to_array_3, one_words){
    char **result = input_to_array("ls", " ");

    cr_assert_str_eq(result[0], "ls");
    cr_assert_null(result[1]);
}

Test(input_to_array_4, lot_of_words){
    char **result = input_to_array("ls -l -a test", " ");

    cr_assert_str_eq(result[0], "ls");
    cr_assert_str_eq(result[1], "-l");
    cr_assert_str_eq(result[2], "-a");
    cr_assert_str_eq(result[3], "test");
    cr_assert_null(result[4]);
}

Test(input_to_array_5, multiple_spaces){
    char **result = input_to_array("ls          -l  -a test\n", " ");

    cr_assert_str_eq(result[0], "ls");
    cr_assert_str_eq(result[1], "-l");
    cr_assert_str_eq(result[2], "-a");
    cr_assert_str_eq(result[3], "test");
    cr_assert_null(result[4]);
}

Test(input_to_array_5, multiple_separator){
    char **result = input_to_array("ls          -l\t-a test", " \t");

    cr_assert_str_eq(result[0], "ls");
    cr_assert_str_eq(result[1], "-l");
    cr_assert_str_eq(result[2], "-a");
    cr_assert_str_eq(result[3], "test");
    cr_assert_null(result[4]);
}
