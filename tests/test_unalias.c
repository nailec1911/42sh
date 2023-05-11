/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "mysh.h"
#include "macro_errors.h"
int do_unalias(mysh_t *mysh, command_t *to_exec);

Test(unalias_1, remove_alias)
{
    mysh_t mysh = {0};
    mysh.alias.tab_file = malloc(sizeof(char *) * 3);
    mysh.alias.tab_file[0] = strdup("alias toto ls\n");
    mysh.alias.tab_file[1] = strdup("alias coco pwd\n");
    char **tab = malloc(sizeof(char *) * 2);
    tab[0] = strdup("alias coco pwd\n");
    tab[1] = NULL;
    command_t to_exec = {0};
    to_exec.args = (char *[3]){"unalias", "toto"};
    mysh.alias.tab_file[2] = NULL;
    do_unalias(&mysh, &to_exec);
    for (int i = 0; !tab[i]; i += 1) {
        cr_assert_str_eq(tab[i], mysh.alias.tab_file[i]);
    }
}

Test(unalias_2, remove_alias)
{
    cr_redirect_stderr();
    mysh_t mysh = {0};
    mysh.alias.tab_file = malloc(sizeof(char *) * 3);
    mysh.alias.tab_file[0] = strdup("alias toto ls\n");
    mysh.alias.tab_file[1] = strdup("alias coco pwd\n");
    command_t to_exec = {0};
    to_exec.args = (char *[3]){"unalias", NULL};
    mysh.alias.tab_file[2] = NULL;
    cr_assert_eq(do_unalias(&mysh, &to_exec), SUCCESS);
    cr_assert_eq(mysh.last_status, 1);
    cr_assert_stderr_eq_str("unalias: Too few arguments.\n");
}
