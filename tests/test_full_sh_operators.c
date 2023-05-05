/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** test_full_sh_operators
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "macro_errors.h"
#include <stdio.h>
#include <unistd.h>
int mysh(char * const env[]);


Test(mysh14, or_command) {
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fprintf(inputs, "env||./tests/hello_world\n");
    fprintf(inputs, "./tests/seggfault||./tests/hello_world\n");
    fprintf(inputs, "./tests/hello_world||./tests/seggfaults\n");
    fprintf(inputs, "exit\n");

    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
    cr_assert_stdout_eq_str("hi\nhello\nthird\nhello world\nhello world\nDONE\n");
}

Test(full_mysh, and_command){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fprintf(inputs, "env&&./tests/hello_world\n");
    fprintf(inputs, "./tests/seggfault&&./tests/hello_world\n");
    fprintf(inputs, "./tests/hello_world&&./tests/seggfault\n");
    fprintf(inputs, "exit\n");

    fclose(inputs);
    cr_assert_eq(mysh(env), 139);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\nSegmentation fault (core dumped)\n");
    cr_assert_stdout_eq_str("hi\nhello\nthird\nhello world\nhello world\n");
}

Test(full_mysh, multiple_operators){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[2] = {"hi"};

    fprintf(inputs, "env&&./tests/seggfault || env ||env && ./tests/seggfault;./tests/hello_world\n");
    fprintf(inputs, "exit\n");

    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
    cr_assert_stdout_eq_str("hi\nhi\nhello world\n");
}
