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
char **my_str_to_word_array(char const *str, char *separator);

Test(my_str_to_word_array_1, two_words){
    char **result = my_str_to_word_array("ls -l", " ");

    cr_assert_str_eq(result[0], "ls");
    cr_assert_str_eq(result[1], "-l");
    cr_assert_null(result[2]);
}

Test(my_str_to_word_array_3, one_words){
    char **result = my_str_to_word_array("ls", " ");

    cr_assert_str_eq(result[0], "ls");
    cr_assert_null(result[1]);
}

Test(my_str_to_word_array_4, lot_of_words){
    char **result = my_str_to_word_array("ls -l -a test", " ");

    cr_assert_str_eq(result[0], "ls");
    cr_assert_str_eq(result[1], "-l");
    cr_assert_str_eq(result[2], "-a");
    cr_assert_str_eq(result[3], "test");
    cr_assert_null(result[4]);
}

Test(my_str_to_word_array_5, multiple_spaces){
    char **result = my_str_to_word_array("ls          -l  -a test\n", " \n");

    cr_assert_str_eq(result[0], "ls");
    cr_assert_str_eq(result[1], "-l");
    cr_assert_str_eq(result[2], "-a");
    cr_assert_str_eq(result[3], "test");
    cr_assert_null(result[4]);
}

Test(my_str_to_word_array_5, multiple_separator){
    char **result = my_str_to_word_array("ls          -l\t-a test", " \t");

    cr_assert_str_eq(result[0], "ls");
    cr_assert_str_eq(result[1], "-l");
    cr_assert_str_eq(result[2], "-a");
    cr_assert_str_eq(result[3], "test");
    cr_assert_null(result[4]);
}
