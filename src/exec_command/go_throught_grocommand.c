/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** go_throught_grocommand
*/

#include "all_args.h"
#include "macro_errors.h"
#include "exec_command.h"

static bool do_exec(all_args_t *all_args, int i)
{
    if (all_args->ast.tab_grocommands[i].type == SEMICOLON)
        return true;
    if (all_args->ast.tab_grocommands[i].type == OPERATOR_OR
    && all_args->to_return != 0)
        return true;
    if (all_args->ast.tab_grocommands[i].type == OPERATOR_AND
    && all_args->to_return == 0)
        return true;
    return false;
}

int go_throught_grocommand(all_args_t *all_args)
{
    int res = 0;
    int exit = 0;
    for (int i = 0; i < all_args->ast.nb_grocommand; i += 1) {
        if (do_exec(all_args, i)) {
        all_args->to_return = all_args->last_status;
        all_args->last_status = 0;
            res = exec_grocommand(all_args, all_args->ast.tab_grocommands[i]);
        }
        if (res == ERROR)
            return ERROR;
        if (res == EXIT)
            exit = EXIT;
    }
    return exit;
}
