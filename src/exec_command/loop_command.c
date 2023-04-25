/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** loop_grocommand
*/

#include "mysh.h"
#include "macro_errors.h"
#include "exec_command.h"

static int loop_and_command(mysh_t *mysh, or_command_t *or_command)
{
    int res = 0;
    int exit = 0;
    int i = 0;

    do {
        mysh->last_status = 0;
        res = exec_and_command(mysh, &(or_command->tab_command[i]));
        if (res == ERROR)
            return ERROR;
        if (res == EXIT)
            exit = EXIT;
        i += 1;
    } while (i < or_command->nb_command && mysh->last_status == SUCCESS);

    return exit;
}

static int loop_or_command(mysh_t *mysh, grocommand_t *grocommand)
{
    int res = 0;
    int exit = 0;
    int i = 0;

    do {
        mysh->last_status = SUCCESS;
        res = loop_and_command(mysh, &(grocommand->tab_command[i]));
        if (res == ERROR)
            return ERROR;
        if (res == EXIT)
            exit = EXIT;
        i += 1;
    } while ( i < grocommand->nb_command && mysh->last_status != SUCCESS);

    return exit;
}

int loop_grocommand(mysh_t *mysh)
{
    int res = 0;
    int exit = 0;

    for (int i = 0; i < mysh->ast.nb_grocommand; i += 1) {
        mysh->last_status = 0;
        res = loop_or_command(mysh, &(mysh->ast.tab_grocommands[i]));
        if (res == ERROR)
            return ERROR;
        if (res == EXIT)
            exit = EXIT;
    }

    return exit;
}
