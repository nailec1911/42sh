/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** handle_input
*/

#ifndef HANDLE_INPUT_H_
    #define HANDLE_INPUT_H_

    #include "mysh.h"

    int add_in_history(mysh_t *mysh, char *input);
    int tokens_to_history(mysh_t *mysh, token_t *list);
    token_t *loop_for_aliases(mysh_t *mysh, token_t *list);
    token_t *loop_for_exclamation_mark(mysh_t *mysh, token_t *list);
    char *is_alias(mysh_t *mysh, char *input);
    int error_in_tokens(mysh_t *mysh, token_t *list);

#endif /* !HANDLE_INPUT_H_ */
