/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "alias.h"
#include <unistd.h>
#include "mysh.h"
#include "macro_errors.h"
int display_alias(char **tab_file, int fd);
int display_specific_alias(char **tab_file, char *to_find, int fd);
char *remake_input(char **tab);

Test(dispay_alias_1, display_all_alias)
{
    cr_redirect_stdout();
    char *tab[3] = {"alias toto ls\n", "alias coco pwd\n", NULL};

    cr_assert_eq(display_alias(tab, 1), SUCCESS);
    cr_assert_stdout_eq_str("alias coco pwd\nalias toto ls\n");
}

Test(dispay_alias_2, wrong_param)
{
    cr_assert_eq(display_alias(NULL, 1), SUCCESS);
}

Test(display_specific_alias_1, display_an_alias)
{
    cr_redirect_stdout();
    char *tab[3] = {"alias toto ls\n", "alias coco pwd\n", NULL};

    cr_assert_eq(display_specific_alias(tab, "toto", 1), SUCCESS);
    cr_assert_stdout_eq_str("ls\n");
}

Test(display_specific_alias_2, display_an_alias)
{
    char *tab[3] = {"alias toto ls\n", "alias coco pwd\n", NULL};

    cr_assert_eq(display_specific_alias(tab, NULL, 1), ERROR);
}

Test(display_specific_alias_3, display_an_alias)
{
    cr_assert_eq(display_specific_alias(NULL, "coco", 1), ERROR);
}

Test(remake_input_1, remake_a_command)
{
    char *tab[4] = {"alias", "coco", "ls -la", NULL};
    cr_assert_str_eq(remake_input(tab), "alias coco ls -la\n");
}

Test(remake_input_2, remake_a_command)
{
    char *tab[4] = {"ls", "-l", "-a", NULL};
    cr_assert_str_eq(remake_input(tab), "ls -l -a\n");
}

Test(remake_input_3, remake_a_command)
{
    cr_assert_null(remake_input(NULL));
}
