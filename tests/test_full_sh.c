/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** test_full_sh
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "macro_errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int mysh(char * const env[]);

Test(full_mysh, simple_command_with_path){
    cr_redirect_stdout();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests", "hello", "third"};

    fprintf(inputs, "hello_world\n");
    fprintf(inputs, "exit\n");
    fflush(inputs);
    fclose(inputs);

    cr_assert_eq(mysh(env), SUCCESS);
    cr_assert_stdout_eq_str("hello world\n");
}

Test(full_mysh, simple_command_full_path){
    cr_redirect_stdout();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests", "hello", "third"};

    fprintf(inputs,"./tests/hello_world\n");
    fprintf(inputs,"exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), SUCCESS);
    cr_assert_stdout_eq_str("hello world\n");
}

Test(full_mysh, error_seggfault){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests", "hello", "third"};

    fprintf(inputs,"seggfault\n");
    fprintf(inputs,"exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), 139);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
}

Test(full_mysh, command_not_found){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests", "hello", "third"};

    fprintf(inputs,"sfdsfds\n");
    fprintf(inputs,"exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), 1);
    cr_assert_stderr_eq_str("sfdsfds: Command not found.\n");
}

Test(full_mysh, builtins_env){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fprintf(inputs,"env\n");
    fprintf(inputs,"exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stdout_eq_str("hi\nhello\nthird\n");
}

Test(full_mysh, piped_function){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fprintf(inputs,"setenv coco | env\n");
    fprintf(inputs,"exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stdout_eq_str("hi\nhello\nthird\n");
}

Test(full_mysh, semicolon_command){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fprintf(inputs,";;env;;;;./tests/hello_world;;;;\n");
    fprintf(inputs,"exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stdout_eq_str("hi\nhello\nthird\nhello world\n");
}

Test(full_mysh, null_function){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fprintf(inputs,"ls |;\n");
    fprintf(inputs,"exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), 1);
    cr_assert_stderr_eq_str("Invalid null command.\n");
}

Test(full_mysh, ambiguous_redirect){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fprintf(inputs,"ls > te| ls\n");
    fprintf(inputs,"ls | ls < l\n");
    fprintf(inputs,"exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), 1);
    cr_assert_stderr_eq_str("Ambiguous output redirect.\nAmbiguous input redirect.\n");
}

Test(full_mysh, redirect){
    cr_redirect_stdout();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests", "hello", "third"};

    fprintf(inputs,"hello_world > temp\n");
    fprintf(inputs,"hello_world < temp\n");
    fprintf(inputs,"exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), SUCCESS);
    cr_assert_stdout_eq_str("hello world\n");
    remove("temp");
}

Test(full_mysh, cd){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fprintf(inputs, "cd tests; ./hello_world; cd -; ./tests/hello_world\n");
    fprintf(inputs, "exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stdout_eq_str("hello world\nhello world\n");
}

Test(full_mysh, double_red_right){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fprintf(inputs,"./tests/hello_world << end\n");
    fprintf(inputs,"dsfdf\nfdfd\nendfdf\nend\n");
    fprintf(inputs,"exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
}

Test(full_mysh, error_zero_divide){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests", "hello", "third"};

    fprintf(inputs,"zero_divide\n");
    fprintf(inputs,"exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), 136);
    cr_assert_stderr_eq_str("Floating exception (core dumped)\n");
}

Test(full_mysh, quotes){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests", "hello", "third"};

    fprintf(inputs,"./tests/disp_args 'hello world' hi\n");
    fprintf(inputs,"exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stdout_eq_str("./tests/disp_args\nhello world\nhi\n");
}

Test(full_mysh, backticks){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests", "hello", "third"};

    fprintf(inputs,"./tests/disp_args `env`\n");
    fprintf(inputs,"exit\n");
    fflush(inputs);
    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stdout_eq_str("./tests/disp_args\nPATH=tests\nhello\nthird\n");
}
