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
int mysh(char * const env[]);


Test(mysh14, or_command){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fwrite("env||./tests/hello_world\n", 1, 25, inputs);
    fwrite("./tests/seggfault||./tests/hello_world\n", 1, 39, inputs);
    fwrite("./tests/hello_world||./test/seggfaults\n", 1, 39, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
    cr_assert_stdout_eq_str("hi\nhello\nthird\nhello world\nhello world\nDONE\n");
}

Test(mysh15, and_command){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fwrite("env&&./tests/hello_world\n", 1, 25, inputs);
    fwrite("./tests/seggfault&&./tests/hello_world\n", 1, 39, inputs);
    fwrite("./tests/hello_world&&./tests/seggfault\n", 1, 39, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), 139);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\nSegmentation fault (core dumped)\n");
    cr_assert_stdout_eq_str("hi\nhello\nthird\nhello world\nhello world\n");
}

Test(mysh16, multiple_operators){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[2] = {"hi"};

    fwrite("env&&./tests/seggfault || env ||env && ./tests/seggfault;./tests/hello_world\n", 1, 77, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
    cr_assert_stdout_eq_str("hi\nhi\nhello world\n");
}