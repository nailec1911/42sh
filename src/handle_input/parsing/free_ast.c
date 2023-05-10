/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** free_ast
*/

#include <stdlib.h>
#include "parser/ast.h"


static void free_command(command_t *command)
{
    if (command->is_ast) {
        free_ast(command->parenthesis);
        free(command->parenthesis);
        return;
    }
    for (int i = 0; i < command->nb_command; i += 1) {
        free(command->args[i]);
    }
    if (command->args != NULL)
        free(command->args);
    if (command->redirect_in.name != NULL)
        free(command->redirect_in.name);
    if (command->redirect_out.name != NULL)
        free(command->redirect_out.name);
}

static void free_or_command(or_command_t *or_command)
{
    if (!or_command->tab_and_command)
        return;
    for (int i = 0; or_command->tab_and_command[i].nb_command != -1; i += 1) {
        for (int j = 0;
        or_command->tab_and_command[i].tab_command[j].nb_command != -1; j += 1)
            free_command(&or_command->tab_and_command[i].tab_command[j]);
        free(or_command->tab_and_command[i].tab_command);
    }
    free(or_command->tab_and_command);
}

static void free_grocommand(grocommand_t *grocommand)
{
    for (int i = 0;
    grocommand->tab_or_command[i].nb_and_command != -1; i += 1) {
        free_or_command(&grocommand->tab_or_command[i]);
    }
    free(grocommand->tab_or_command);
}

void free_ast(ast_t *ast)
{
    if (!ast)
        return;
    for (int i = 0; ast->tab_grocommands[i].nb_or_command != -1; i += 1) {
        free_grocommand(&ast->tab_grocommands[i]);
    }
    free(ast->tab_grocommands);
}
