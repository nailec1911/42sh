/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include "macro_errors.h"
#include "mysh.h"
#include "history.h"
int do_history(mysh_t *mysh, command_t to_exec);
history_t create_history();
int compare_char(char **command, int i, history_t *history);

Test(history1, normal_history)
{
    cr_redirect_stdout();
    mysh_t mysh = {0};

    command_t command = {0};
    command.args = (char *[2]){"history"};
    mysh.history = create_history();
    mysh.last_status = 0;
    cr_assert_eq(do_history(&mysh, command), SUCCESS);
    cr_assert_eq(mysh.last_status, 0);
}

Test(history2, null_mysh)
{
    mysh_t mysh = {0};

    command_t command = {0};
    command.args = (char *[2]){"history"};
    mysh.history = create_history();
    mysh.last_status = 0;
    cr_assert_eq(do_history(NULL, command), ERROR);
    cr_assert_eq(mysh.last_status, 0);
}

Test(history3, wrong_args)
{
    mysh_t mysh = {0};
    char *tab[3] = {"history", "-w", NULL};

    mysh.history = create_history();
    cr_assert_eq(compare_char(tab, 1, &(mysh.history)), ERROR);
}

Test(history4, wrong_args)
{
    mysh_t mysh = {0};
    char *tab[3] = {"history", "w", NULL};
    mysh.history = create_history();

    cr_assert_eq(compare_char(tab, 1, &(mysh.history)), ERROR);
}
