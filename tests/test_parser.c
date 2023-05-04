/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** test_parser
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "str_func.h"
#include "parser/token.h"
#include "mysh.h"
#include "macro_errors.h"
int handle_input(mysh_t *mysh, char *input);
int get_ast(mysh_t *mysh, char *input);
void free_ast(ast_t ast);

Test(parser1, only_ls){
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, "ls -l -a\n"), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_or_command, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_or_command[0].nb_and_command, 1);
    and_command_t tree_leef = mysh.ast.tab_grocommands[0].tab_or_command[0].tab_and_command[0];

    cr_assert_eq(tree_leef.nb_command, 1);
    cr_assert_eq(tree_leef.tab_command[0].is_last, true);
    cr_assert_eq(tree_leef.tab_command[0].fd_in, STDIN_FILENO);
    cr_assert_eq(tree_leef.tab_command[0].fd_out, STDOUT_FILENO);

    cr_assert_eq(tree_leef.tab_command[0].redirect_out.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[0].redirect_in.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[0].nb_command, 3);
    cr_assert_str_eq(tree_leef.tab_command[0].args[0], "ls");
    cr_assert_str_eq(tree_leef.tab_command[0].args[1], "-l");
    cr_assert_str_eq(tree_leef.tab_command[0].args[2], "-a");
    free_ast(mysh.ast);
}

Test(parser2, piped_command){
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, "ls -l -a | grep src|cat -e\n"), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_or_command, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_or_command[0].nb_and_command, 1);
    and_command_t tree_leef = mysh.ast.tab_grocommands[0].tab_or_command[0].tab_and_command[0];

    cr_assert_eq(tree_leef.nb_command, 3);
    cr_assert_eq(tree_leef.tab_command[0].is_last, false);
    cr_assert_eq(tree_leef.tab_command[0].fd_in, STDIN_FILENO);
    cr_assert_eq(tree_leef.tab_command[0].redirect_out.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[0].redirect_in.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[0].nb_command, 3);
    cr_assert_str_eq(tree_leef.tab_command[0].args[0], "ls");
    cr_assert_str_eq(tree_leef.tab_command[0].args[1], "-l");
    cr_assert_str_eq(tree_leef.tab_command[0].args[2], "-a");

    cr_assert_eq(tree_leef.tab_command[1].is_last, false);
    cr_assert_eq(tree_leef.tab_command[1].redirect_out.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[1].redirect_in.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[1].nb_command, 2);
    cr_assert_str_eq(tree_leef.tab_command[1].args[0], "grep");
    cr_assert_str_eq(tree_leef.tab_command[1].args[1], "src");

    cr_assert_eq(tree_leef.tab_command[2].is_last, true);
    cr_assert_eq(tree_leef.tab_command[2].fd_out, STDOUT_FILENO);
    cr_assert_eq(tree_leef.tab_command[2].redirect_out.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[2].redirect_in.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[2].nb_command, 2);
    cr_assert_str_eq(tree_leef.tab_command[2].args[0], "cat");
    cr_assert_str_eq(tree_leef.tab_command[2].args[1], "-e");
    free_ast(mysh.ast);
}

Test(parser3, redirection_simple){
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, "< in cat > out\n"), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_or_command, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_or_command[0].nb_and_command, 1);
    and_command_t tree_leef = mysh.ast.tab_grocommands[0].tab_or_command[0].tab_and_command[0];

    cr_assert_eq(tree_leef.nb_command, 1);
    cr_assert_eq(tree_leef.tab_command[0].is_last, true);
    cr_assert_eq(tree_leef.tab_command[0].fd_in, STDIN_FILENO);
    cr_assert_eq(tree_leef.tab_command[0].fd_out, STDOUT_FILENO);

    cr_assert_eq(tree_leef.tab_command[0].redirect_in.type, REDIRECT_IN_1);
    cr_assert_str_eq(tree_leef.tab_command[0].redirect_in.name, "in");
    cr_assert_eq(tree_leef.tab_command[0].redirect_out.type, REDIRECT_OUT_1);
    cr_assert_str_eq(tree_leef.tab_command[0].redirect_out.name, "out");
    cr_assert_eq(tree_leef.tab_command[0].nb_command, 1);
    cr_assert_str_eq(tree_leef.tab_command[0].args[0], "cat");
    free_ast(mysh.ast);
}

Test(parser4, redirection_double){
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, "<< in cat >> out\n"), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_or_command, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_or_command[0].nb_and_command, 1);
    and_command_t tree_leef = mysh.ast.tab_grocommands[0].tab_or_command[0].tab_and_command[0];

    cr_assert_eq(tree_leef.nb_command, 1);
    cr_assert_eq(tree_leef.tab_command[0].is_last, true);
    cr_assert_eq(tree_leef.tab_command[0].fd_in, STDIN_FILENO);
    cr_assert_eq(tree_leef.tab_command[0].fd_out, STDOUT_FILENO);

    cr_assert_eq(tree_leef.tab_command[0].redirect_in.type, REDIRECT_IN_2);
    cr_assert_str_eq(tree_leef.tab_command[0].redirect_in.name, "in");
    cr_assert_eq(tree_leef.tab_command[0].redirect_out.type, REDIRECT_OUT_2);
    cr_assert_str_eq(tree_leef.tab_command[0].redirect_out.name, "out");
    cr_assert_eq(tree_leef.tab_command[0].nb_command, 1);
    cr_assert_str_eq(tree_leef.tab_command[0].args[0], "cat");
    free_ast(mysh.ast);
}

Test(parser5, ambiguous_redirection_in){
    cr_redirect_stderr();
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, "cat < in < in2\n"), FAILURE);
    cr_assert_eq(mysh.last_status, 1);
    free_ast(mysh.ast);
    cr_assert_stderr_eq_str("Ambiguous input redirect.\n");
}

Test(parser5, ambiguous_redir_in_2){
    cr_redirect_stderr();
    mysh_t mysh = {0};
    cr_assert_eq(get_ast(&mysh, "cat << in << in2\n"), FAILURE);
    cr_assert_eq(mysh.last_status, 1);
    free_ast(mysh.ast);
    cr_assert_stderr_eq_str("Ambiguous input redirect.\n");
}

Test(parser5, ambiguous_redir_in3){
    cr_redirect_stderr();
    mysh_t mysh = {0};
    cr_assert_eq(get_ast(&mysh, "ls | cat < in\n"), FAILURE);
    cr_assert_eq(mysh.last_status, 1);
    cr_assert_stderr_eq_str("Ambiguous input redirect.\n");
    free_ast(mysh.ast);
}

Test(parser6, ambiguous_redirection_out){
    cr_redirect_stderr();
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, "cat > in > in2\n"), FAILURE);
    cr_assert_eq(mysh.last_status, 1);
    cr_assert_stderr_eq_str("Ambiguous output redirect.\n");
}

Test(parser6, ambiguous_redirection_out_2){

    cr_redirect_stderr();
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, "cat >> in >> in2\n"), FAILURE);
    cr_assert_eq(mysh.last_status, 1);
    cr_assert_stderr_eq_str("Ambiguous output redirect.\n");
}

Test(parser6, ambiguous_redirection_out_3){
    cr_redirect_stderr();
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, "cat > in | ls\n"), FAILURE);
    cr_assert_eq(mysh.last_status, 1);
    free_ast(mysh.ast);
    cr_assert_stderr_eq_str("Ambiguous output redirect.\n");
}

Test(parser7, missing_redirect_name){
    cr_redirect_stderr();
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, "cat < < in2\n"), FAILURE);
    cr_assert_eq(mysh.last_status, 1);

    cr_assert_stderr_eq_str("Missing name for redirect.\n");
}

Test(parser8, null_command){
    cr_redirect_stderr();
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, "ls|;\n"), FAILURE);
    cr_assert_eq(mysh.last_status, 1);

    cr_assert_stderr_eq_str("Invalid null command.\n");
}

void assert_command_ok(and_command_t to_test)
{
    cr_assert_eq(to_test.nb_command, 1);
    cr_assert_eq(to_test.tab_command[0].is_last, true);
    cr_assert_eq(to_test.tab_command[0].fd_in, STDIN_FILENO);
    cr_assert_eq(to_test.tab_command[0].fd_out, STDOUT_FILENO);
    cr_assert_eq(to_test.tab_command[0].redirect_out.type, NO_REDIRECT);
    cr_assert_eq(to_test.tab_command[0].redirect_in.type, NO_REDIRECT);

    cr_assert_eq(to_test.tab_command[0].nb_command, 2);
    cr_assert_str_eq(to_test.tab_command[0].args[0], "ls");
    cr_assert_str_eq(to_test.tab_command[0].args[1], "-l");
}

Test(parser9, grocommand){
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, ";;;;ls -l;;; ls -l\n"), SUCCESS);

    ast_t ast = mysh.ast;
    cr_assert_eq(ast.nb_grocommand, 2);

    for (int i = 0; i < 2; i += 1) {
        assert_command_ok(ast.tab_grocommands[i].tab_or_command[0].tab_and_command[0]);
    }
    free_ast(mysh.ast);
}

Test(parser10, or_command){
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh,"ls -l || ls -l || ls -l\n"), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    grocommand_t to_test = mysh.ast.tab_grocommands[0];
    cr_assert_eq(to_test.nb_or_command, 3);

    for (int i = 0; i < 3; i += 1) {
        assert_command_ok(to_test.tab_or_command[i].tab_and_command[0]);
    }
    free_ast(mysh.ast);
}

Test(parser11, and_command){
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, "ls -l && ls -l && ls -l\n"), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_or_command, 1);
    or_command_t to_test = mysh.ast.tab_grocommands[0].tab_or_command[0];
    cr_assert_eq(to_test.nb_and_command, 3);

    for (int i = 0; i < 3; i += 1) {
        assert_command_ok(to_test.tab_and_command[i]);
    }
    free_ast(mysh.ast);
}

Test(parser12, all_operators){
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, "ls -l && ls -l || ls -l;"
    "ls -l||ls -l &&ls -l &&ls -l || ls -l\n"), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 2);

    // ------------------ first grocommand ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_or_command, 2);
            //    ------- first or_command ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_or_command[0].nb_and_command, 2);
    assert_command_ok(mysh.ast.tab_grocommands[0].tab_or_command[0].tab_and_command[0]);
    assert_command_ok(mysh.ast.tab_grocommands[0].tab_or_command[0].tab_and_command[1]);
            //    ------- second or_command ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_or_command[1].nb_and_command, 1);
    assert_command_ok(mysh.ast.tab_grocommands[0].tab_or_command[1].tab_and_command[0]);


    // ------------------ second grocommand ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[1].nb_or_command, 3);
            //    ------- first or_command ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[1].tab_or_command[0].nb_and_command, 1);
    assert_command_ok(mysh.ast.tab_grocommands[1].tab_or_command[0].tab_and_command[0]);
            //    ------- second or_command ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[1].tab_or_command[1].nb_and_command, 3);
    assert_command_ok(mysh.ast.tab_grocommands[1].tab_or_command[1].tab_and_command[0]);
    assert_command_ok(mysh.ast.tab_grocommands[1].tab_or_command[1].tab_and_command[1]);
    assert_command_ok(mysh.ast.tab_grocommands[1].tab_or_command[1].tab_and_command[2]);
            //    ------- third or_command ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[1].tab_or_command[2].nb_and_command, 1);
    assert_command_ok(mysh.ast.tab_grocommands[1].tab_or_command[2].tab_and_command[0]);
    free_ast(mysh.ast);
}

Test(parser13, quotes){
    mysh_t mysh = {0};

    cr_assert_eq(get_ast(&mysh, "ls -l 'ds ds' `ddd`\n"), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_or_command, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_or_command[0].nb_and_command, 1);
    and_command_t tree_leef = mysh.ast.tab_grocommands[0].tab_or_command[0].tab_and_command[0];

    cr_assert_eq(tree_leef.nb_command, 1);
    cr_assert_eq(tree_leef.tab_command[0].is_last, true);
    cr_assert_eq(tree_leef.tab_command[0].fd_in, STDIN_FILENO);
    cr_assert_eq(tree_leef.tab_command[0].fd_out, STDOUT_FILENO);

    cr_assert_eq(tree_leef.tab_command[0].redirect_out.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[0].redirect_in.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[0].nb_command, 4);
    cr_assert_str_eq(tree_leef.tab_command[0].args[0], "ls");
    cr_assert_str_eq(tree_leef.tab_command[0].args[1], "-l");
    cr_assert_str_eq(tree_leef.tab_command[0].args[2], "ds ds");
    cr_assert_str_eq(tree_leef.tab_command[0].args[3], "ddd`");
    free_ast(mysh.ast);
}
