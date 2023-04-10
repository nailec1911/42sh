/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** go_throught_grocommand
*/

#include "all_args.h"
#include "macro_errors.h"
#include "exec_command.h"

static bool do_exec(all_args_t *all_args, int i, bool prev_executed)
{
    if (all_args->ast.tab_grocommands[i].type == SEMICOLON)
        return true;
    if (all_args->ast.tab_grocommands[i].type == OPERATOR_OR
    && all_args->last_status != 0)
        return true;
    if (all_args->ast.tab_grocommands[i].type == OPERATOR_AND
    && all_args->last_status == 0 && prev_executed)
        return true;
    return false;
}

int go_throught_grocommand(all_args_t *all_args)
{
    int res = 0;
    int exit = 0;
    bool prev_executed = false;

    for (int i = 0; i < all_args->ast.nb_grocommand; i += 1) {
        if (do_exec(all_args, i, prev_executed)) {
            all_args->to_return = all_args->last_status;
            all_args->last_status = 0;
            res = exec_grocommand(all_args, all_args->ast.tab_grocommands[i]);
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
