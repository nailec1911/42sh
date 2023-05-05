/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** set_all_ast
*/

#include <unistd.h>
#include <stdio.h>
#include <str_func.h>
#include "mysh.h"
#include "macro_errors.h"
int set_all_ast(ast_t *ast);

static int error_redirect(int type)
{
    if (type == REDIRECT_IN_1 || type == REDIRECT_IN_2)
        fprintf(stderr, "Ambiguous input redirect.\n");
    if (type == REDIRECT_OUT_1 || type == REDIRECT_OUT_2)
        fprintf(stderr, "Ambiguous output redirect.\n");
    fflush(stderr);
    return FAILURE;
}

static int check_no_redirect(command_t *command, int i)
{
    if (command->redirect_in.type != NO_REDIRECT && i != 0)
        return error_redirect(command->redirect_in.type);

    if (command->redirect_out.type != NO_REDIRECT && command->is_last == false)
        return error_redirect(command->redirect_out.type);

    return SUCCESS;
}

static int set_and_command(and_command_t *and_command)
{
    int res = 0;
    int i = 0;

    and_command->tab_command[and_command->nb_command - 1].is_last = true;
    for (; i < and_command->nb_command; i += 1) {
        res = check_no_redirect(&(and_command->tab_command[i]), i);
        if (res != SUCCESS)
            return res;
    }
    return SUCCESS;
}

static int set_or_command(or_command_t *or_command)
{
    int res = SUCCESS;

    for (int i = 0; i < or_command->nb_and_command; i += 1) {
        if ((res = set_and_command(&(or_command->tab_and_command[i])))
                != SUCCESS)
            return res;
    }
    return SUCCESS;
}

int set_all_ast(ast_t *ast)
{
    int res = 0;

    for (int i = 0; i < ast->nb_grocommand; i += 1) {
        for (int j = 0; j < ast->tab_grocommands[i].nb_or_command
            && res == SUCCESS; j += 1)
            res = set_or_command(&(ast->tab_grocommands[i].tab_or_command[j]));
        if (res != SUCCESS)
            return res;
    }
    return SUCCESS;
}
