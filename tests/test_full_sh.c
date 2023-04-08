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
int mysh(char * const env[]);

Test(mysh1, simple_command_with_path){
    cr_redirect_stdout();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests/", "hello", "third"};

    fwrite("hello_world\n", 1, 12, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), SUCCESS);
    cr_assert_stdout_eq_str("hello world\n");
}

Test(mysh2, simple_command_full_path){
    cr_redirect_stdout();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests/", "hello", "third"};

    fwrite("./tests/hello_world\n", 1, 20, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), SUCCESS);
    cr_assert_stdout_eq_str("hello world\n");
}

Test(mysh3, error_seggfault){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests/", "hello", "third"};

    fwrite("./tests/seggfault\n", 1, 18, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), 139);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
}

Test(mysh4, command_not_found){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests/", "hello", "third"};

    fwrite("sfdsfds\n", 1, 8, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), 1);
    cr_assert_stderr_eq_str("sfdsfds: Command not found.\n");
}

Test(mysh5, builtins_env){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fwrite("env\n", 1, 4, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stdout_eq_str("hi\nhello\nthird\n");
}

Test(mysh6, piped_function){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fwrite("setenv coco | env\n", 1, 18, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stdout_eq_str("hi\nhello\nthird\n");
}

Test(mysh7, semicolon_command){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fwrite(";;env;;;;./tests/hello_world;;;;\n", 1, 33, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stdout_eq_str("hi\nhello\nthird\nhello world\n");
}

Test(mysh8, null_function){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fwrite("ls |;\n", 1, 6, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), 1);
    cr_assert_stderr_eq_str("Invalid null command.\n");
}

Test(mysh9, ambiguous_redirect){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fwrite("ls > te| ls\n", 1, 12, inputs);
    fwrite("ls | ls < l\n", 1, 12, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), 1);
    cr_assert_stderr_eq_str("Ambiguous output redirect.\nAmbiguous input redirect.\n");
}

Test(mysh10, redirect){
    cr_redirect_stdout();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests/", "hello", "third"};

    fwrite("hello_world > tests/temp\n", 1, 25, inputs);
    fwrite("hello_world < tests/temp\n", 1, 25, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), SUCCESS);
    cr_assert_stdout_eq_str("hello world\n");
}

Test(mysh11, cd){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fwrite("cd src; ./hello_world; cd -; ./tests/hello_world\n", 1, 50, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
    cr_assert_stdout_eq_str("hello world\nhello world\n");
}

Test(mysh12, double_red_right){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"hi", "hello", "third"};

    fwrite("./tests/hello_world << end\n", 1, 27, inputs);
    fwrite("dsfdf\nfdfd\nendfdf\nend\n", 1, 22, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), 0);
}

Test(mysh13, error_zero_divide){
    cr_redirect_stdout();
    cr_redirect_stderr();
    FILE *inputs = cr_get_redirected_stdin();
    char *const env[4] = {"PATH=tests/", "hello", "third"};

    fwrite("./tests/zero_divide\n", 1, 20, inputs);
    fwrite("exit\n", 1, 5, inputs);

    fclose(inputs);
    cr_assert_eq(mysh(env), 136);
    cr_assert_stderr_eq_str("Floating exception (core dumped)\n");
}