/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** free_ast
*/

#include "stdlib.h"
#include "parser/ast.h"

static void free_command(command_t command)
{
    for (int i = 0; i < command.nb_command; i += 1) {
        free(command.command[i]);
    }
    if (command.command != NULL)
        free(command.command);
    if (command.redirect_in.name != NULL)
        free(command.redirect_in.name);
    if (command.redirect_out.name != NULL)
        free(command.redirect_out.name);
}

static void free_or_command(or_command_t or_command)
{
    for (int i = 0; or_command.tab_command[i].nb_command != -1; i += 1) {
        for (int j = 0;
        or_command.tab_command[i].tab_command[j].nb_command != -1; j += 1)
            free_command(or_command.tab_command[i].tab_command[j]);
        free(or_command.tab_command[i].tab_command);
    }
    free(or_command.tab_command);
}

static void free_grocommand(grocommand_t grocommand)
{
    for (int i = 0; grocommand.tab_command[i].nb_command != -1 ; i += 1) {
        free_or_command(grocommand.tab_command[i]);
    }
    free(grocommand.tab_command);
}

void free_ast(ast_t ast)
{
    for (int i = 0; ast.tab_grocommands[i].nb_command != -1; i += 1) {
        free_grocommand(ast.tab_grocommands[i]);
    }
    free(ast.tab_grocommands);
}
