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
#include "str_func.h"
#include "parser/token.h"
#include "mysh.h"
#include "macro_errors.h"
int parse_input(char *input, mysh_t *mysh);

Test(parser1, only_ls){
    mysh_t mysh = {0};

    char *input = my_str_dup("ls -l -a\n");
    cr_assert_eq(parse_input(input, &mysh), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_command, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_command[0].nb_command, 1);
    and_command_t tree_leef = mysh.ast.tab_grocommands[0].tab_command[0].tab_command[0];

    cr_assert_eq(tree_leef.nb_command, 1);
    cr_assert_eq(tree_leef.tab_command[0].is_last, true);
    cr_assert_eq(tree_leef.tab_command[0].fd_in, STDIN_FILENO);
    cr_assert_eq(tree_leef.tab_command[0].fd_out, STDOUT_FILENO);

    cr_assert_eq(tree_leef.tab_command[0].redirect_out.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[0].redirect_in.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[0].nb_command, 3);
    cr_assert_str_eq(tree_leef.tab_command[0].command[0], "ls");
    cr_assert_str_eq(tree_leef.tab_command[0].command[1], "-l");
    cr_assert_str_eq(tree_leef.tab_command[0].command[2], "-a");
}

Test(parser2, piped_command){
    mysh_t mysh = {0};

    char *input = my_str_dup("ls -l -a | grep src|cat -e\n");
    cr_assert_eq(parse_input(input, &mysh), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_command, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_command[0].nb_command, 1);
    and_command_t tree_leef = mysh.ast.tab_grocommands[0].tab_command[0].tab_command[0];

    cr_assert_eq(tree_leef.nb_command, 3);
    cr_assert_eq(tree_leef.tab_command[0].is_last, false);
    cr_assert_eq(tree_leef.tab_command[0].fd_in, STDIN_FILENO);
    cr_assert_eq(tree_leef.tab_command[0].redirect_out.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[0].redirect_in.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[0].nb_command, 3);
    cr_assert_str_eq(tree_leef.tab_command[0].command[0], "ls");
    cr_assert_str_eq(tree_leef.tab_command[0].command[1], "-l");
    cr_assert_str_eq(tree_leef.tab_command[0].command[2], "-a");

    cr_assert_eq(tree_leef.tab_command[1].is_last, false);
    cr_assert_eq(tree_leef.tab_command[1].redirect_out.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[1].redirect_in.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[1].nb_command, 2);
    cr_assert_str_eq(tree_leef.tab_command[1].command[0], "grep");
    cr_assert_str_eq(tree_leef.tab_command[1].command[1], "src");

    cr_assert_eq(tree_leef.tab_command[2].is_last, true);
    cr_assert_eq(tree_leef.tab_command[2].fd_out, STDOUT_FILENO);
    cr_assert_eq(tree_leef.tab_command[2].redirect_out.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[2].redirect_in.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[2].nb_command, 2);
    cr_assert_str_eq(tree_leef.tab_command[2].command[0], "cat");
    cr_assert_str_eq(tree_leef.tab_command[2].command[1], "-e");
}

Test(parser3, redirection_simple){
    mysh_t mysh = {0};

    char *input = my_str_dup("< in cat > out\n");
    cr_assert_eq(parse_input(input, &mysh), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_command, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_command[0].nb_command, 1);
    and_command_t tree_leef = mysh.ast.tab_grocommands[0].tab_command[0].tab_command[0];

    cr_assert_eq(tree_leef.nb_command, 1);
    cr_assert_eq(tree_leef.tab_command[0].is_last, true);
    cr_assert_eq(tree_leef.tab_command[0].fd_in, STDIN_FILENO);
    cr_assert_eq(tree_leef.tab_command[0].fd_out, STDOUT_FILENO);

    cr_assert_eq(tree_leef.tab_command[0].redirect_in.type, IN_1);
    cr_assert_str_eq(tree_leef.tab_command[0].redirect_in.name, "in");
    cr_assert_eq(tree_leef.tab_command[0].redirect_out.type, OUT_1);
    cr_assert_str_eq(tree_leef.tab_command[0].redirect_out.name, "out");
    cr_assert_eq(tree_leef.tab_command[0].nb_command, 1);
    cr_assert_str_eq(tree_leef.tab_command[0].command[0], "cat");
}

Test(parser4, redirection_double){
    mysh_t mysh = {0};

    char *input = my_str_dup("<< in cat >> out\n");
    cr_assert_eq(parse_input(input,  &mysh), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_command, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_command[0].nb_command, 1);
    and_command_t tree_leef = mysh.ast.tab_grocommands[0].tab_command[0].tab_command[0];

    cr_assert_eq(tree_leef.nb_command, 1);
    cr_assert_eq(tree_leef.tab_command[0].is_last, true);
    cr_assert_eq(tree_leef.tab_command[0].fd_in, STDIN_FILENO);
    cr_assert_eq(tree_leef.tab_command[0].fd_out, STDOUT_FILENO);

    cr_assert_eq(tree_leef.tab_command[0].redirect_in.type, IN_2);
    cr_assert_str_eq(tree_leef.tab_command[0].redirect_in.name, "in");
    cr_assert_eq(tree_leef.tab_command[0].redirect_out.type, OUT_2);
    cr_assert_str_eq(tree_leef.tab_command[0].redirect_out.name, "out");
    cr_assert_eq(tree_leef.tab_command[0].nb_command, 1);
    cr_assert_str_eq(tree_leef.tab_command[0].command[0], "cat");
}

Test(parser5, ambiguous_redirection_in){
    cr_redirect_stderr();
    mysh_t mysh = {0};

    char *input = my_str_dup("cat < in < in2\n");
    cr_assert_eq(parse_input(input, &mysh), FAILURE);
    cr_assert_eq(mysh.last_status, 1);

    mysh.last_status = 0;
    char *input2 = my_str_dup("cat << in << in2\n");
    cr_assert_eq(parse_input(input2, &mysh), FAILURE);
    cr_assert_eq(mysh.last_status, 1);

    mysh.last_status = 0;
    char *input3 = my_str_dup("ls | cat < in\n");
    cr_assert_eq(parse_input(input3, &mysh), FAILURE);
    cr_assert_eq(mysh.last_status, 1);
    cr_assert_stderr_eq_str("Ambiguous input redirect.\nAmbiguous input redirect.\nAmbiguous input redirect.\n");
}

Test(parser6, ambiguous_redirection_out){
    cr_redirect_stderr();
    mysh_t mysh = {0};

    char *input = my_str_dup("cat > in > in2\n");
    cr_assert_eq(parse_input(input, &mysh), FAILURE);
    cr_assert_eq(mysh.last_status, 1);

    mysh.last_status = 0;
    char *input2 = my_str_dup("cat >> in >> in2\n");
    cr_assert_eq(parse_input(input2, &mysh), FAILURE);
    cr_assert_eq(mysh.last_status, 1);

    mysh.last_status = 0;
    char *input3 = my_str_dup("cat > in | ls\n");
    cr_assert_eq(parse_input(input3, &mysh), FAILURE);
    cr_assert_eq(mysh.last_status, 1);

    cr_assert_stderr_eq_str("Ambiguous output redirect.\nAmbiguous output redirect.\nAmbiguous output redirect.\n");
}

Test(parser7, missing_redirect_name){
    cr_redirect_stderr();
    mysh_t mysh = {0};

    char *input = my_str_dup("cat < < in2\n");
    cr_assert_eq(parse_input(input, &mysh), FAILURE);
    cr_assert_eq(mysh.last_status, 1);

    cr_assert_stderr_eq_str("missing name\n");
}

Test(parser8, null_command){
    cr_redirect_stderr();
    mysh_t mysh = {0};

    char *input = my_str_dup("ls|;\n");
    cr_assert_eq(parse_input(input, &mysh), FAILURE);
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
    cr_assert_str_eq(to_test.tab_command[0].command[0], "ls");
    cr_assert_str_eq(to_test.tab_command[0].command[1], "-l");
}

Test(parser9, grocommand){
    mysh_t mysh = {0};

    char *input = my_str_dup(";;;;ls -l;;; ls -l\n");
    cr_assert_eq(parse_input(input, &mysh), SUCCESS);

    ast_t ast = mysh.ast;
    cr_assert_eq(ast.nb_grocommand, 2);

    for (int i = 0; i < 2; i += 1) {
        assert_command_ok(ast.tab_grocommands[i].tab_command[0].tab_command[0]);
    }
}

Test(parser10, or_command){
    mysh_t mysh = {0};

    char *input = my_str_dup("ls -l || ls -l || ls -l\n");
    cr_assert_eq(parse_input(input, &mysh), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    grocommand_t to_test = mysh.ast.tab_grocommands[0];
    cr_assert_eq(to_test.nb_command, 3);

    for (int i = 0; i < 3; i += 1) {
        assert_command_ok(to_test.tab_command[i].tab_command[0]);
    }
}

Test(parser11, and_command){
    mysh_t mysh = {0};

    char *input = my_str_dup("ls -l && ls -l && ls -l\n");
    cr_assert_eq(parse_input(input, &mysh), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_command, 1);
    or_command_t to_test = mysh.ast.tab_grocommands[0].tab_command[0];
    cr_assert_eq(to_test.nb_command, 3);

    for (int i = 0; i < 3; i += 1) {
        assert_command_ok(to_test.tab_command[i]);
    }
}

Test(parser12, all_operators){
    mysh_t mysh = {0};

    char *input = my_str_dup("ls -l && ls -l || ls -l; ls -l||ls -l &&ls -l &&ls -l || ls -l\n");
    cr_assert_eq(parse_input(input, &mysh), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 2);

    // ------------------ first grocommand ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_command, 2);
    //            ------- first or_command ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_command[0].nb_command, 2);
    assert_command_ok(mysh.ast.tab_grocommands[0].tab_command[0].tab_command[0]);
    assert_command_ok(mysh.ast.tab_grocommands[0].tab_command[0].tab_command[1]);
    //            ------- second or_command ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_command[1].nb_command, 1);
    assert_command_ok(mysh.ast.tab_grocommands[0].tab_command[1].tab_command[0]);


    // ------------------ second grocommand ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[1].nb_command, 3);
    //            ------- first or_command ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[1].tab_command[0].nb_command, 1);
    assert_command_ok(mysh.ast.tab_grocommands[1].tab_command[0].tab_command[0]);
    //            ------- second or_command ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[1].tab_command[1].nb_command, 3);
    assert_command_ok(mysh.ast.tab_grocommands[1].tab_command[1].tab_command[0]);
    assert_command_ok(mysh.ast.tab_grocommands[1].tab_command[1].tab_command[1]);
    assert_command_ok(mysh.ast.tab_grocommands[1].tab_command[1].tab_command[2]);
    //            ------- third or_command ----------------------
    cr_assert_eq(mysh.ast.tab_grocommands[1].tab_command[2].nb_command, 1);
    assert_command_ok(mysh.ast.tab_grocommands[1].tab_command[2].tab_command[0]);
}

Test(parser13, quotes){
    mysh_t mysh = {0};

    char *input = my_str_dup("ls -l 'ds ds' `ddd`\n");
    cr_assert_eq(parse_input(input, &mysh), SUCCESS);

    cr_assert_eq(mysh.ast.nb_grocommand, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].nb_command, 1);
    cr_assert_eq(mysh.ast.tab_grocommands[0].tab_command[0].nb_command, 1);
    and_command_t tree_leef = mysh.ast.tab_grocommands[0].tab_command[0].tab_command[0];

    cr_assert_eq(tree_leef.nb_command, 1);
    cr_assert_eq(tree_leef.tab_command[0].is_last, true);
    cr_assert_eq(tree_leef.tab_command[0].fd_in, STDIN_FILENO);
    cr_assert_eq(tree_leef.tab_command[0].fd_out, STDOUT_FILENO);

    cr_assert_eq(tree_leef.tab_command[0].redirect_out.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[0].redirect_in.type, NO_REDIRECT);
    cr_assert_eq(tree_leef.tab_command[0].nb_command, 4);
    cr_assert_str_eq(tree_leef.tab_command[0].command[0], "ls");
    cr_assert_str_eq(tree_leef.tab_command[0].command[1], "-l");
    cr_assert_str_eq(tree_leef.tab_command[0].command[2], "ds ds");
    cr_assert_str_eq(tree_leef.tab_command[0].command[3], "ddd`");
}
