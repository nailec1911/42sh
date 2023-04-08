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
    free(command.command);
    if (command.redirect_in.name != NULL)
        free(command.redirect_in.name);
    if (command.redirect_out.name != NULL)
        free(command.redirect_out.name);
}

static void free_grocommand(grocommand_t grocommand)
{
    for (int i = 0; i < grocommand.nb_command; i += 1) {
        free_command(grocommand.tab_command[i]);
    }
    free(grocommand.tab_command);
}

void free_ast(ast_t ast)
{
    for (int i = 0; i < ast.nb_grocommand; i += 1) {
        free_grocommand(ast.tab_grocommands[i]);
    }
    free(ast.tab_grocommands);
}
