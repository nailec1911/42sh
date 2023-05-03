/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** get_command
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "str_func.h"
#include "parser/token.h"
#include "parser/ast.h"
#include "macro_errors.h"

static void error_redirect(int type)
{
    if (type == REDIRECT_IN_1 || type == REDIRECT_IN_2)
        fprintf(stderr, "Ambiguous input redirect.\n");
    if (type == REDIRECT_OUT_1 || type == REDIRECT_OUT_2)
        fprintf(stderr, "Ambiguous output redirect.\n");
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
        fprintf(stderr, "missing name\n");
        return;
    }
    if (redirect.type == REDIRECT_IN_1 || redirect.type == REDIRECT_IN_2) {
        set_redirect(parser, &command->redirect_in,
        redirect.type, parser->list_tokens[parser->cursor].value);
    }
    if (redirect.type == REDIRECT_OUT_1 || redirect.type == REDIRECT_OUT_2) {
        set_redirect(parser, &command->redirect_out,
        redirect.type, parser->list_tokens[parser->cursor].value);
    }
    parser->cursor += 1;
}

static int add_elt_in_tab(parser_t *parser, command_t *command)
{
    char ** temp = command->args;
    command->nb_command += 1;

    if ((command->args=
    malloc(sizeof(char *) * (command->nb_command + 1))) == NULL)
        return ERROR;

    for (int i = 0; i < command->nb_command - 1; i += 1)
        command->args[i] = temp[i];

    command->args[command->nb_command - 1] =
    parser->list_tokens[parser->cursor].value;

    command->args[command->nb_command] = NULL;

    parser->cursor += 1;
    if (temp != NULL)
        free(temp);
    return SUCCESS;
}

command_t get_command(parser_t *parser)
{
    command_t new = {0, NULL, NULL, false, STDIN_FILENO, STDOUT_FILENO,
    false, {NO_REDIRECT, NULL}, {NO_REDIRECT, NULL}, 0, 0};

    while (IS_REDIRECT(parser->list_tokens[parser->cursor].type)
    || parser->list_tokens[parser->cursor].type == IDENTIFIER) {
        if (parser->list_tokens[parser->cursor].type == IDENTIFIER
        && add_elt_in_tab(parser, &new) == ERROR) {
            parser->error = ERROR;
            return new;
        }
        if (IS_REDIRECT(parser->list_tokens[parser->cursor].type))
            handle_redirect(parser, &new);
    }
    if (parser->list_tokens[parser->cursor].type == UNMATCHED_QUOTE) {
        parser->error = 1;
    } else if (new.args== NULL) {
        parser->error = 1;
        fprintf(stderr, "Invalid null command.\n");
    }
    return new;
}
