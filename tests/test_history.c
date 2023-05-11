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
int do_history(mysh_t *mysh, command_t *to_exec);
int detect_flags(command_t *to_exec, history_t *history);
int compare_char(char **command, int i, history_t *history);
char *do_exclamation_mark(mysh_t *mysh, char *input);

Test(history1, display_history){
    cr_redirect_stdout();
    mysh_t mysh = {0};
    mysh.history = create_history();
    command_t to_exec = {0};
    to_exec.args = (char *[3]){"history", "-w"};

    to_exec.fd_out = 1;
    cr_assert_eq(do_history(&mysh, &to_exec), SUCCESS);
    // cr_assert_stdout_eq_str("Usage: history [-chrSLMT] [# number of events].\n");
    cr_assert_eq(mysh.last_status, 1);
}

Test(history2, detect_flags)
{
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.args = (char *[3]){"history", "-h"};
    cr_assert_eq(detect_flags(&to_exec, &mysh.history), SUCCESS);
    cr_assert_eq(mysh.history.flags, FLAG_H);
}

Test(history3, detect_wrong_flags_1)
{
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.args = (char *[3]){"history", "-w"};
    cr_assert_eq(detect_flags(&to_exec, &mysh.history), ERROR);
    cr_assert_eq(mysh.history.flags, NO_FLAG);
}

Test(history4, detect_wrong_flags_2)
{
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.args = (char *[3]){"history", "a"};
    cr_assert_eq(detect_flags(&to_exec, &mysh.history), ERROR);
    cr_assert_eq(mysh.history.flags, NO_FLAG);
}

Test(history5, detect_wrong_flags_3)
{
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.args = (char *[3]){"history", "-"};
    cr_assert_eq(detect_flags(&to_exec, &mysh.history), ERROR);
    cr_assert_eq(mysh.history.flags, NO_FLAG);
}

Test(history6, detect_wrong_flags_4)
{
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.args = (char *[4]){"history", "-h", "-"};
    cr_assert_eq(detect_flags(&to_exec, &mysh.history), ERROR);
    cr_assert_eq(mysh.history.flags, NO_FLAG);
}

Test(history7, detect_wrong_flags_5)
{
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.args = (char *[5]){"history", "-h", "-h", " "};
    cr_assert_eq(detect_flags(&to_exec, &mysh.history), ERROR);
    cr_assert_eq(mysh.history.flags, NO_FLAG);
}

Test(history7, detect_wrong_flags_6)
{
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.args = (char *[5]){"history", "-h", "-hr", "az"};
    cr_assert_eq(detect_flags(&to_exec, &mysh.history), ERROR);
    cr_assert_eq(mysh.history.flags, NO_FLAG);
}

Test(history8, detect_wrong_flags_7)
{
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.args = (char *[5]){"history", "toto", "-hr", "az"};
    cr_assert_eq(detect_flags(&to_exec, &mysh.history), ERROR);
    cr_assert_eq(mysh.history.flags, NO_FLAG);
}

Test(history9, multiple_flags_1)
{
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.args = (char *[3]){"history", "-hr"};
    cr_assert_eq(detect_flags(&to_exec, &mysh.history), SUCCESS);
    cr_assert_eq(mysh.history.flags, FLAG_H | FLAG_R);
}

Test(history10, multiple_flags_2)
{
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.args = (char *[4]){"history", "-hr", "-c"};
    cr_assert_eq(detect_flags(&to_exec, &mysh.history), SUCCESS);
    cr_assert_eq(mysh.history.flags, FLAG_H | FLAG_R | FLAG_C);
}

Test(history11, multiple_flags_3)
{
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.args = (char *[5]){"history", "-h", "-c", "-r"};
    cr_assert_eq(detect_flags(&to_exec, &mysh.history), SUCCESS);
    cr_assert_eq(mysh.history.flags, FLAG_H | FLAG_R | FLAG_C);
}

Test(history12, wrong_param_1)
{
    mysh_t mysh = {0};

    mysh.history = create_history();
    cr_assert_eq(detect_flags(NULL, &mysh.history), ERROR);
    cr_assert_eq(mysh.history.flags, NO_FLAG);
}

Test(history13, wrong_param_2)
{
    mysh_t mysh = {0};

    mysh.history = create_history();
    cr_assert_eq(detect_flags(NULL, NULL), ERROR);
    cr_assert_eq(mysh.history.flags, NO_FLAG);
}

Test(history14, wrong_param_3)
{
    mysh_t mysh = {0};

    mysh.history = create_history();
    cr_assert_eq(compare_char(NULL, 1, &mysh.history), ERROR);
    cr_assert_eq(mysh.history.flags, NO_FLAG);
}

Test(history15, wrong_param_4)
{
    mysh_t mysh = {0};
    char **tab = malloc(sizeof(char *) * 1);
    tab[0] = NULL;

    mysh.history = create_history();
    cr_assert_eq(compare_char(tab, 1, &mysh.history), ERROR);
    cr_assert_eq(mysh.history.flags, NO_FLAG);
}

Test(history16, opt_clear)
{
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.args = (char *[3]){"history", "-c"};
    cr_assert_eq(do_history(&mysh, &to_exec), SUCCESS);
    cr_assert_eq(mysh.history.flags, FLAG_C);
    cr_assert_str_eq(mysh.history.tab_hist[0]->command, "alias toto ls\n");
    cr_assert_str_eq(mysh.history.tab_hist[0]->num, "     3");
    cr_assert_str_eq(mysh.history.tab_hist[0]->time, "01:50");
    cr_assert_eq(mysh.last_status, SUCCESS);
}

Test(history17, opt_h)
{
    cr_redirect_stdout();
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.fd_out = 1;
    to_exec.args = (char *[3]){"history", "-h"};
    cr_assert_eq(do_history(&mysh, &to_exec), SUCCESS);
    cr_assert_eq(mysh.history.flags, FLAG_H);
    // cr_assert_stdout_eq_str("ls\necho hello\nalias toto ls\n");
    cr_assert_eq(mysh.last_status, SUCCESS);
}

Test(history18, opt_r)
{
    cr_redirect_stdout();
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.fd_out = 1;
    to_exec.args = (char *[3]){"history", "-rh"};
    cr_assert_eq(do_history(&mysh, &to_exec), SUCCESS);
    cr_assert_eq(mysh.history.flags, FLAG_H | FLAG_R);
    // cr_assert_stdout_eq_str("alias toto ls\necho hello\nls\n");
    cr_assert_eq(mysh.last_status, SUCCESS);
}

Test(history19, exclamation_mark_num)
{
    cr_redirect_stdout();
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.fd_out = 1;
    to_exec.args = (char *[2]){"!2"};
    cr_assert_eq(do_exclamation_mark(&mysh, to_exec.args[1]), SUCCESS);
    cr_assert_eq(mysh.last_status, SUCCESS);
    // cr_assert_stdout_eq_str("hello\n");
}

Test(history20, exclamation_mark_string)
{
    cr_redirect_stdout();
    mysh_t mysh = {0};
    command_t to_exec = {0};

    mysh.history = create_history();
    to_exec.fd_out = 1;
    to_exec.args = (char *[2]){"!echo"};
    cr_assert_eq(do_exclamation_mark(&mysh, to_exec.args[1]), SUCCESS);
    cr_assert_eq(mysh.last_status, SUCCESS);
    // cr_assert_stdout_eq_str("hello\n");
}

Test(history21, exclamation_mark_wrong_1)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
    mysh_t mysh = {0};
    char *input = strdup("!1000\n");

    mysh.history = create_history();
    cr_assert_eq(do_exclamation_mark(&mysh, input), SUCCESS);
    cr_assert_eq(mysh.last_status, 1);
    cr_assert_stderr_eq_str("1000: Event not found.\n");
}

Test(history22, exclamation_mark_wrong_2)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
    mysh_t mysh = {0};
    char *input = strdup("!tutu\n");

    mysh.history = create_history();
    cr_assert_eq(do_exclamation_mark(&mysh, input), SUCCESS);
    cr_assert_eq(mysh.last_status, 1);
    cr_assert_stderr_eq_str("tutu: Event not found.\n");
}

Test(history23, exclamation_mark_wrong_3)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
    mysh_t mysh = {0};
    char *str = strdup("!\n");

    mysh.history = create_history();
    cr_assert_eq(do_exclamation_mark(&mysh, str), SUCCESS);
    cr_assert_eq(mysh.last_status, 1);
    cr_assert_stderr_eq_str("!: Command not found.\n");
}
