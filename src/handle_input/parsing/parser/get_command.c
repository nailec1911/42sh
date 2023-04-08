/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** get_command
*/

#include <stdlib.h>
#include <unistd.h>
#include "str_func.h"
#include "parser/token.h"
#include "parser/ast.h"
#include "macro_errors.h"

static void error_redirect(int type)
{
    if (type == IN_1 || type == IN_2)
        my_putstr("Ambiguous input redirect.\n", 2);
    if (type == OUT_1 || type == OUT_2)
        my_putstr("Ambiguous output redirect.\n", 2);
}

static void set_redirect(parser_t *parser,
redirect_t *redirect, int new_type, char *name)
{
    if (redirect->type != NO_REDIRECT) {
        parser->error = 1;
        free(name);
        return error_redirect(redirect->type);
    }
    redirect->type = new_type;
    redirect->name = name;
}

static void handle_redirect(parser_t *parser, command_t *command)
{
    token_t redirect = parser->list_tokens[parser->cursor];
    parser->cursor += 1;

    if (parser->list_tokens[parser->cursor].type != IDENTIFIER){
        command->nb_command = -1;
        parser->error = 1;
        my_putstr("missing name\n", 2);
        return;
    }
    if (redirect.size_val == IN_1 || redirect.size_val == IN_2) {
        set_redirect(parser, &command->redirect_in,
        redirect.size_val, parser->list_tokens[parser->cursor].value);
    }
    if (redirect.size_val == OUT_1 || redirect.size_val == OUT_2) {
        set_redirect(parser, &command->redirect_out,
        redirect.size_val, parser->list_tokens[parser->cursor].value);
    }
    parser->cursor += 1;
}

static int add_elt_in_tab(parser_t *parser, command_t *command)
{
    char ** temp = command->command;
    command->nb_command += 1;

    if ((command->command =
    malloc(sizeof(char *) * (command->nb_command + 1))) == NULL)
        return ERROR;

    for (int i = 0; i < command->nb_command - 1; i += 1)
        command->command[i] = temp[i];

    command->command[command->nb_command - 1] =
    parser->list_tokens[parser->cursor].value;

    command->command[command->nb_command] = NULL;

    parser->cursor += 1;
    if (temp != NULL)
        free(temp);
    return SUCCESS;
}

command_t get_command(parser_t *parser)
{
    command_t new = {0, NULL, NULL, false, STDIN_FILENO, STDOUT_FILENO,
    false, {NO_REDIRECT, NULL}, {NO_REDIRECT, NULL}};

    while (parser->list_tokens[parser->cursor].type == REDIRECT
    || parser->list_tokens[parser->cursor].type == IDENTIFIER) {

        if (parser->list_tokens[parser->cursor].type == IDENTIFIER
        && add_elt_in_tab(parser, &new) == ERROR) {
            parser->error = ERROR;
            return new;
        }

        if (parser->list_tokens[parser->cursor].type == REDIRECT)
            handle_redirect(parser, &new);
    }
    if (new.command == NULL) {
        parser->error = 1;
        my_putstr("Invalid null command.\n", 2);
    }
    return new;
}
