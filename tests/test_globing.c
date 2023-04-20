/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** test_globing
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <unistd.h>
#include "macro_errors.h"
#include "mysh.h"
#include "parser/parse.h"
int mysh(char * const env[]);
int update_glob_argv(and_command_t *cmd);
int get_ast(mysh_t *mysh, char *input);

Test(unit_globings1, star_in_arg){
    cr_redirect_stderr();
    mysh_t mysh = {0};
    chdir("tests/");
    char *input = "./disp_args test_full*.c\n";

    cr_assert_eq(get_ast(&(mysh), input), SUCCESS);
    cr_assert_eq(mysh.last_status, 0);
    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_command, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_command[0].nb_command, 1);

    and_command_t *cmd = &(mysh.ast.tab_grocommands[0].tab_command[0].tab_command[0]);
    cr_assert_eq(cmd->nb_command, 1);
    update_glob_argv(cmd);
    cr_assert_eq(cmd->tab_command[0].nb_command, 3);
    char **args = cmd->tab_command[0].command;

    cr_assert_str_eq(args[0], "./disp_args");
    cr_assert_str_eq(args[1], "test_full_sh.c");
    cr_assert_str_eq(args[2], "test_full_sh_operators.c");
}

Test(unit_globings2, question_mark){
    cr_redirect_stderr();
    mysh_t mysh = {0};

    chdir("tests/");

    char *input = "./disp_args hello?world\n";
    cr_assert_eq(get_ast(&mysh, input), SUCCESS);
    cr_assert_eq(mysh.last_status, 0);
    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_command, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_command[0].nb_command, 1);

    and_command_t *cmd = &(mysh.ast.tab_grocommands[0].tab_command[0].tab_command[0]);
    cr_assert_eq(cmd->nb_command, 1);
    update_glob_argv(cmd);
    cr_assert_eq(cmd->tab_command[0].nb_command, 3);
    char **args = cmd->tab_command[0].command;

    cr_assert_str_eq(args[0], "./disp_args");
    cr_assert_str_eq(args[1], "hello2world");
    cr_assert_str_eq(args[2], "hello_world");
}

Test(unit_globings3, brackets){
    cr_redirect_stderr();
    mysh_t mysh = {0};

    chdir("tests/");

    char *input = strdup("./disp_args t[1-3]\n");
    cr_assert_eq(get_ast(&mysh, input), SUCCESS);
    cr_assert_eq(mysh.last_status, 0);
    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_command, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_command[0].nb_command, 1);

    and_command_t *cmd = &(mysh.ast.tab_grocommands[0].tab_command[0].tab_command[0]);
    cr_assert_eq(cmd->nb_command, 1);
    update_glob_argv(cmd);
    cr_assert_eq(cmd->tab_command[0].nb_command, 4);
    char **args = cmd->tab_command[0].command;

    cr_assert_str_eq(args[0], "./disp_args");
    cr_assert_str_eq(args[1], "t1");
    cr_assert_str_eq(args[2], "t2");
    cr_assert_str_eq(args[3], "t3");
}

Test(mysh_globings1, star){
    cr_redirect_stdout();
    chdir("tests/");
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests/", "hello", "third"};

    fwrite("./disp_args test_full*.c\n", 1, 25, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), SUCCESS);
    cr_assert_stdout_eq_str("./disp_args\ntest_full_sh.c\ntest_full_sh_operators.c\n");
}

Test(mysh_globings2, question_mark){
    cr_redirect_stdout();
    chdir("tests/");
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests/", "hello", "third"};

    fwrite("./disp_args hello?world\n", 1, 24, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), SUCCESS);
    cr_assert_stdout_eq_str("./disp_args\nhello2world\nhello_world\n");
}

Test(mysh_globings3, brackets){
    cr_redirect_stdout();
    chdir("tests/");
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests/", "hello", "third"};

    fwrite("./disp_args t[1-3]\n", 1, 19, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), SUCCESS);
    cr_assert_stdout_eq_str("./disp_args\nt1\nt2\nt3\n");
}

Test(mysh_globings4, no_globs){
    cr_redirect_stdout();
    chdir("tests/");
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests/", "hello", "third"};

    fwrite("./disp_args t1\n", 1, 15, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), SUCCESS);
    cr_assert_stdout_eq_str("./disp_args\nt1\n");
}

Test(mysh_globings5, no_match){
    cr_redirect_stdout();
    cr_redirect_stderr();
    chdir("tests/");
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests/", "hello", "third"};

    fwrite("./disp_args *.d\n", 1, 16, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), SUCCESS);
    cr_assert_stdout_eq_str("./disp_args: No match.\n");
}
