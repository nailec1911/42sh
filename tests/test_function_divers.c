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
history_t create_history(void);
tab_hist_t **create_tab_hist(void);
int get_nb_line(char *filepath);
int add_elem_tab(history_t *history, char *to_add, int num);
char **file_to_tab(char *filepath);
int file_to_tab_hist(char *filepath, history_t *history);

Test(get_nb_line_1, get_nb_line_in_file)
{
    char filepath[] = "tests/count_line_test";
    cr_assert_eq(get_nb_line(filepath), 5);
}

Test(get_nb_line_2, wrong_filepath)
{
    char filepath[] = "wrong_filepath";
    cr_assert_eq(get_nb_line(filepath), -1);
}

Test(get_nb_line_3, null_param)
{
    cr_assert_eq(get_nb_line(NULL), ERROR);
}

Test(add_elem_tab_1, add_an_element_in_tab)
{
    mysh_t mysh = {0};
    mysh.history = create_history();
    char *to_add = strdup("ls");

    mysh.history.num_cmd += 1;
    cr_assert_eq(add_elem_tab(&mysh.history, to_add, mysh.history.num_cmd), SUCCESS);
    cr_assert_not_null(mysh.history.tab_hist[3]->command);
    cr_assert_not_null(mysh.history.tab_hist[3]->num);
    cr_assert_not_null(mysh.history.tab_hist[3]->time);
    cr_assert_str_eq(mysh.history.tab_hist[3]->command, "ls");
    cr_assert_str_eq(mysh.history.tab_hist[3]->num, "     4");
    cr_assert_eq(mysh.history.len_tab_hist, 4);
}

Test(add_elem_tab_2, wrong_params)
{
    mysh_t mysh = {0};
    mysh.history = create_history();
    char *to_add = strdup("ls");

    mysh.history.num_cmd += 1;
    mysh.history.len_tab_hist = -1;
    cr_assert_eq(add_elem_tab(&mysh.history, to_add, mysh.history.num_cmd), ERROR);
    cr_assert_null(mysh.history.tab_hist[3]);
}

Test(add_elem_tab_3, wrong_params)
{
    mysh_t mysh = {0};
    mysh.history = create_history();

    mysh.history.num_cmd += 1;
    cr_assert_eq(add_elem_tab(NULL, NULL, mysh.history.num_cmd), ERROR);
    cr_assert_null(mysh.history.tab_hist[3]);
}

Test(file_to_tab_1, load_file_to_tab)
{
    char filepath[] = "tests/file_to_tab_test";
    char **tab = file_to_tab(filepath);
    char **tab_ref = (char *[4]){"alias toto ls\n", "alias coco pwd\n", "alias a echo hello\n"};

    cr_assert_not_null(tab);
    cr_assert_not_null(tab[0]);
    cr_assert_not_null(tab[1]);
    cr_assert_not_null(tab[2]);
    cr_assert_null(tab[3]);
    for (int i = 0; tab_ref[i]; i += 1) {
        cr_assert_str_eq(tab[i], tab_ref[i]);
    }
}

Test(file_to_tab_2, wrong_filepath)
{
    char filepath[] = "wrong_filepath";
    char **tab = file_to_tab(filepath);

    cr_assert_null(tab);
}

Test(file_to_tab_3, wrong_syntax_file)
{
    char filepath[] = "tests/file_to_tab_wrong_test";
    char **tab = file_to_tab(filepath);

    cr_assert_not_null(tab);
    cr_assert_null(tab[0]);
}

Test(file_to_tab_hist_1, load_history_file_in_tab)
{
    mysh_t mysh = {0};
    char filepath[] = "tests/fake_history";
    tab_hist_t **tab_ref = create_tab_hist();

    cr_assert_eq(file_to_tab_hist(filepath, &mysh.history), SUCCESS);
    cr_assert_not_null(mysh.history.tab_hist);
    cr_assert_not_null(mysh.history.tab_hist[0]);
    cr_assert_not_null(mysh.history.tab_hist[1]);
    cr_assert_not_null(mysh.history.tab_hist[2]);
    cr_assert_null(mysh.history.tab_hist[3]);
    for (int i = 0; tab_ref[i]; i += 1) {
        cr_assert_str_eq(mysh.history.tab_hist[i]->command, tab_ref[i]->command);
        cr_assert_str_eq(mysh.history.tab_hist[i]->time, tab_ref[i]->time);
        cr_assert_str_eq(mysh.history.tab_hist[i]->num, tab_ref[i]->num);
    }
}

Test(file_to_tab_hist_2, wrong_filepath)
{
    mysh_t mysh = {0};
    char filepath[] = "wrong_filepath";

    cr_assert_eq(file_to_tab_hist(filepath, &mysh.history), ERROR);
    cr_assert_null(mysh.history.tab_hist);
}

Test(file_to_tab_hist_3, wrong_syntax_1)
{
    mysh_t mysh = {0};
    char filepath[] = "tests/fake_history_wrong_1";
    tab_hist_t **tab_ref = malloc(sizeof(tab_hist_t *) * 3);
    tab_ref[0] = malloc(sizeof(tab_hist_t));
    tab_ref[0]->command = strdup("ls -la\n");
    tab_ref[0]->num = strdup("     2");
    tab_ref[0]->time = strdup("01:01");
    tab_ref[1] = malloc(sizeof(tab_hist_t));
    tab_ref[1]->command = strdup("pwd\n");
    tab_ref[1]->num = strdup("     3");
    tab_ref[1]->time = strdup("23:01");
    tab_ref[2] = NULL;

    cr_assert_eq(file_to_tab_hist(filepath, &mysh.history), SUCCESS);
    cr_assert_not_null(mysh.history.tab_hist[0]);
    cr_assert_not_null(mysh.history.tab_hist[1]);
    cr_assert_null(mysh.history.tab_hist[2]);
    for (int i = 0; tab_ref[i]; i += 1) {
        cr_assert_str_eq(mysh.history.tab_hist[i]->command, tab_ref[i]->command);
        cr_assert_str_eq(mysh.history.tab_hist[i]->num, tab_ref[i]->num);
        cr_assert_str_eq(mysh.history.tab_hist[i]->time, tab_ref[i]->time);
    }
}

Test(file_to_tab_hist_4, wrong_syntax_2)
{
    mysh_t mysh = {0};
    char filepath[] = "tests/fake_history_wrong_2";

    tab_hist_t **tab_ref = malloc(sizeof(tab_hist_t *) * 2);
    tab_ref[0] = malloc(sizeof(tab_hist_t));
    tab_ref[0]->command = strdup("ls -la\n");
    tab_ref[0]->num = strdup("     2");
    tab_ref[0]->time = strdup("01:01");
    tab_ref[1] = NULL;

    cr_assert_eq(file_to_tab_hist(filepath, &mysh.history), SUCCESS);
    cr_assert_not_null(mysh.history.tab_hist[0]);
    cr_assert_null(mysh.history.tab_hist[1]);
    for (int i = 0; tab_ref[i]; i += 1) {
        cr_assert_str_eq(mysh.history.tab_hist[i]->command, tab_ref[i]->command);
        cr_assert_str_eq(mysh.history.tab_hist[i]->num, tab_ref[i]->num);
        cr_assert_str_eq(mysh.history.tab_hist[i]->time, tab_ref[i]->time);
    }
}

Test(file_to_tab_hist_4, wrong_syntax_3)
{
    mysh_t mysh = {0};
    char filepath[] = "tests/fake_history_wrong_3";
    tab_hist_t **tab_ref = malloc(sizeof(tab_hist_t *) * 3);
    tab_ref[0] = malloc(sizeof(tab_hist_t));
    tab_ref[0]->command = strdup("ls -la\n");
    tab_ref[0]->num = strdup("     2");
    tab_ref[0]->time = strdup("01:01");
    tab_ref[1] = malloc(sizeof(tab_hist_t));
    tab_ref[1]->command = strdup("pwd\n");
    tab_ref[1]->num = strdup("     3");
    tab_ref[1]->time = strdup("23:01");
    tab_ref[2] = NULL;

    cr_assert_eq(file_to_tab_hist(filepath, &mysh.history), SUCCESS);
    cr_assert_not_null(mysh.history.tab_hist[0]);
    cr_assert_not_null(mysh.history.tab_hist[1]);
    cr_assert_null(mysh.history.tab_hist[2]);
    for (int i = 0; tab_ref[i]; i += 1) {
        cr_assert_str_eq(mysh.history.tab_hist[i]->command, tab_ref[i]->command);
        cr_assert_str_eq(mysh.history.tab_hist[i]->num, tab_ref[i]->num);
        cr_assert_str_eq(mysh.history.tab_hist[i]->time, tab_ref[i]->time);
    }
}

Test(file_to_tab_hist_5, wrong_syntax_4)
{
    mysh_t mysh = {0};
    char filepath[] = "tests/fake_history_wrong_4";
    tab_hist_t **tab_ref = malloc(sizeof(tab_hist_t *) * 2);
    tab_ref[0] = malloc(sizeof(tab_hist_t));
    tab_ref[0]->command = strdup("ls -la\n");
    tab_ref[0]->num = strdup("     2");
    tab_ref[0]->time = strdup("01:01");
    tab_ref[1] = NULL;

    cr_assert_eq(file_to_tab_hist(filepath, &mysh.history), SUCCESS);
    cr_assert_not_null(mysh.history.tab_hist[0]);
    cr_assert_null(mysh.history.tab_hist[1]);
    for (int i = 0; tab_ref[i]; i += 1) {
        cr_assert_str_eq(mysh.history.tab_hist[i]->command, tab_ref[i]->command);
        cr_assert_str_eq(mysh.history.tab_hist[i]->num, tab_ref[i]->num);
        cr_assert_str_eq(mysh.history.tab_hist[i]->time, tab_ref[i]->time);
    }
}
