/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** go_through_grocommand
*/

#include "mysh.h"
#include "macro_errors.h"
#include "exec_command.h"
int exec_and_command(mysh_t *mysh, and_command_t *to_exec);

static int go_through_and_command(mysh_t *mysh, or_command_t *or_command)
{
    int res = 0;
    int exit = 0;

    for (int i = 0; i < or_command->nb_command; i += 1) {
        mysh->to_return = mysh->last_status;
        mysh->last_status = 0;
        res = exec_and_command(mysh, &(or_command->tab_command[i]));
        if (res == ERROR)
            return ERROR;
        if (res == EXIT)
            exit = EXIT;
    }
    return exit;
}

static int go_through_or_command(mysh_t *mysh, grocommand_t *grocommand)
{
    int res = 0;
    int exit = 0;

    for (int i = 0; i < grocommand->nb_command; i += 1) {
        mysh->to_return = mysh->last_status;
        mysh->last_status = 0;
        res = go_through_and_command(mysh, &(grocommand->tab_command[i]));
        if (res == ERROR)
            return ERROR;
        if (res == EXIT)
            exit = EXIT;
    }
    return exit;
}

int go_through_grocommand(mysh_t *mysh)
{
    int res = 0;
    int exit = 0;

    for (int i = 0; i < mysh->ast.nb_grocommand; i += 1) {
        mysh->to_return = mysh->last_status;
        mysh->last_status = 0;
        res = go_through_or_command(mysh, &(mysh->ast.tab_grocommands[i]));
        if (res == ERROR)
            return ERROR;
        if (res == EXIT)
            exit = EXIT;
    }
    return exit;
}
