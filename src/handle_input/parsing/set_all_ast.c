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

static int error_redirect(int type)
{
    if (type == IN_1 || type == IN_2)
        fprintf(stderr, "Ambiguous input redirect.\n");
    if (type == OUT_1 || type == OUT_2)
        fprintf(stderr, "Ambiguous output redirect.\n");
    return FAILURE;
}

static int set_redirect_command(command_t *command, int red_in, int red_out)
{
    if (red_in != STDIN_FILENO && command->redirect_in.type != NO_REDIRECT)
        return error_redirect(command->redirect_in.type);
    command->fd_in = red_in;

    if (red_out != STDOUT_FILENO && command->redirect_out.type != NO_REDIRECT)
        return error_redirect(command->redirect_out.type);
    command->fd_out = red_out;

    return SUCCESS;
}

static int set_and_command(and_command_t *grocommand)
{
    int pipefd[2];
    int last = STDIN_FILENO;
    int res = 0;
    int i = 0;

    for (; i < grocommand->nb_command - 1; i += 1) {
        if (pipe(pipefd) == -1)
            return ERROR;
        res = set_redirect_command(
        &(grocommand->tab_command[i]), last, pipefd[1]);
        if (res != SUCCESS)
            return res;
        last = pipefd[0];
    }
    res = set_redirect_command
    (&(grocommand->tab_command[i]), last, STDOUT_FILENO);
    if (res != SUCCESS)
        return res;
    grocommand->tab_command[grocommand->nb_command - 1].is_last = true;
    return SUCCESS;
}

static int set_or_command(or_command_t *or_command)
{
    int res = SUCCESS;

    for (int i = 0; i < or_command->nb_command; i += 1) {
        if ((res = set_and_command(&(or_command->tab_command[i]))) != SUCCESS)
            return res;
    }
    return SUCCESS;
}

int set_all_ast(ast_t *ast)
{
    int res = 0;

    for (int i = 0; i < ast->nb_grocommand; i += 1) {
        for (int j = 0; j < ast->tab_grocommands[i].nb_command
            && res == SUCCESS; j += 1)
            res = set_or_command(&(ast->tab_grocommands[i].tab_command[j]));
        if (res != SUCCESS)
            return res;
    }
    return SUCCESS;
}
