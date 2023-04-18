/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell1-celian.lombardot
** File description:
** test_handle_error
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sys/wait.h>
int handle_errors(int status);

Test(handle_error1, no_error){
    cr_assert_eq(handle_errors(0), 0);
}

Test(handle_error2, seggfault_core_dump){
    cr_redirect_stderr();
    cr_assert_eq(handle_errors(139), 139);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
}

Test(handle_error3, fpe_core_dump){
    cr_redirect_stderr();
    cr_assert_eq(handle_errors(136), 136);
    cr_assert_stderr_eq_str("Floating exception (core dumped)\n");
}

Test(handle_error4, exit_status){
    cr_assert_eq(handle_errors(3328), 1);
    cr_assert_eq(handle_errors(2048), 126);
}

Test(handle_error4, fpe_core_dump){
    cr_redirect_stderr();
    cr_assert_eq(handle_errors(136), 136);
    cr_assert_stderr_eq_str("Floating exception (core dumped)\n");
}
