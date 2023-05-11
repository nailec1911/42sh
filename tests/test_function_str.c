/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "history.h"
#include <unistd.h>
#include "mysh.h"
#include "macro_errors.h"
#include "str_func.h"
char *remake_command(char **tab);
char *clean_last_input(char **tab_alias);
char *remove_first_char(char *input);
char *num_to_str(int num);

Test(remake_command_1, remove_useless_word)
{
    char *tab[5] = {"alias", "toto", "ls", "-la", NULL};
    char *str = remake_command(tab);
    cr_assert_not_null(str);
    cr_assert_str_eq(str, "ls -la");
}

Test(remake_command_2, wrong_param)
{
    cr_assert_null(remake_command(NULL));
}

Test(clean_last_input_1, add_back_slash)
{
    char *tab[5] = {"alias", "toto", "ls", "-la", NULL};
    char *str = clean_last_input(tab);
    cr_assert_not_null(str);
    cr_assert_str_eq(str, "ls -la\n");
}

Test(clean_last_input_2, wrong_param)
{
    cr_assert_null(clean_last_input(NULL));
}

Test(num_to_str, create_num_str_for_history)
{
    cr_assert_str_eq(num_to_str(2), "     2");
}

Test(is_in_1, check_if_char_is_in_str)
{
    cr_assert_eq(is_in('a', "Marius"), 0);
}

Test(is_in_2, check_if_char_is_in_str)
{
    cr_assert_eq(is_in('a', "EPITECH"), 1);
}

Test(my_strstrlen, length_tab)
{
    char *tab[5] = {"hello", "world", "coco", "nicolas", NULL};
    cr_assert_eq(my_strstrlen(tab), 4);
    cr_assert_eq(my_strstrlen(NULL), 0);
}

Test(is_num_char, check_if_str_is_is_num_and_char)
{
    cr_assert_eq(is_num_char("     2", ' '), true);
    cr_assert_eq(is_num_char("284512", '\0'), true);
    cr_assert_eq(is_num_char("20:52", ':'), true);
    cr_assert_eq(is_num_char("20z:52", ':'), false);
}

Test(count_word, count_the_word_number)
{
    cr_assert_eq(count_word("ls -l -a", " "), 3);
    cr_assert_eq(count_word("ls -l -a\n", "\n"), 1);
    cr_assert_eq(count_word("ls -l -a", NULL), 0);
    cr_assert_eq(count_word(NULL, " |&"), 0);
}
