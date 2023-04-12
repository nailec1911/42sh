/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** go_throught_grocommand
*/

#include "mysh.h"
#include "macro_errors.h"
#include "exec_command.h"

static bool do_exec(mysh_t *mysh, int i, bool prev_executed)
{
    if (mysh->ast.tab_grocommands[i].type == SEMICOLON)
        return true;
    if (mysh->ast.tab_grocommands[i].type == OPERATOR_OR
    && mysh->last_status != 0)
        return true;
    if (mysh->ast.tab_grocommands[i].type == OPERATOR_AND
    && mysh->last_status == 0 && prev_executed)
        return true;
    return false;
}

int go_throught_grocommand(mysh_t *mysh)
{
    int res = 0;
    int exit = 0;
    bool prev_executed = false;

    for (int i = 0; i < mysh->ast.nb_grocommand; i += 1) {
        if (do_exec(mysh, i, prev_executed)) {
            mysh->to_return = mysh->last_status;
            mysh->last_status = 0;
            res = exec_grocommand(mysh, mysh->ast.tab_grocommands[i]);
            prev_executed = true;
        } else {
            prev_executed = false;
        }
        if (res == ERROR)
            return ERROR;
        if (res == EXIT)
            exit = EXIT;
    }
    return exit;
}
