/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_input
*/

#ifndef HANDLE_INPUT_H_
    #define HANDLE_INPUT_H_

    #include "mysh.h"

    int handle_input(mysh_t *mysh, char *input);
    char *replace_exclamation_mark(mysh_t *mysh, char *input);
    int tokens_to_history(mysh_t *mysh, token_t *list);
    int add_in_history(history_t *history, char *input);
    token_t *loop_for_aliases(mysh_t *mysh, token_t *list);
    token_t *quote_and_inhib(mysh_t *mysh, token_t *list);
    int replace_var(mysh_t *mysh, token_t *token);
    int error_in_tokens(mysh_t *mysh, token_t *list);
    char *is_alias(alias_t *alias, char *input);
    int remove_inhibitors(char *command);

#endif /* !HANDLE_INPUT_H_ */
