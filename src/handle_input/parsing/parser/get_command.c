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
#include "parser/create_ast.h"
#include "macro_errors.h"

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
    token_t redirect = parser_peek(parser);
    parser->cursor += 1;

    if (parser_peek(parser).type != IDENTIFIER){
        command->nb_command = -1;
        parser->error = 1;
        fprintf(stderr, "Missing name for redirect.\n");
        return;
    }
    if (redirect.type == REDIRECT_IN_1 || redirect.type == REDIRECT_IN_2) {
        set_redirect(parser, &command->redirect_in,
        redirect.type, parser_peek(parser).value);
    }
    if (redirect.type == REDIRECT_OUT_1 || redirect.type == REDIRECT_OUT_2) {
        set_redirect(parser, &command->redirect_out,
        redirect.type, parser_peek(parser).value);
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
    command->command[command->nb_command - 1] = parser_peek(parser).value;
    command->command[command->nb_command] = NULL;
    parser->cursor += 1;
    if (temp != NULL)
        free(temp);
    return SUCCESS;
}

command_t get_command(parser_t *parser)
{
    command_t new = {false, NULL, 0, NULL, NULL, false, STDIN_FILENO,
    STDOUT_FILENO, false, {NO_REDIRECT, NULL}, {NO_REDIRECT, NULL}};

    while (!END_CMD(parser_peek(parser)) && parser->error == SUCCESS) {
        if (parser_peek(parser).type == L_PARENTHESIS
        && get_ast_parenthesis(parser, &new) != SUCCESS)
            return new;
        if (parser_peek(parser).type == IDENTIFIER
        && add_elt_in_tab(parser, &new) == ERROR) {
            parser->error = ERROR;
            return new;
        }
        if (IS_REDIRECT(parser_peek(parser).type))
            handle_redirect(parser, &new);
    }
    check_error(parser, new);
    return new;
}
