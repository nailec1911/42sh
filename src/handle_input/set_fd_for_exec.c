/*
** EPITECH PROJECT, 2023
** B-PSU-200-BDX-2-1-minishell2-celian.lombardot
** File description:
** set_fd_input
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"
#include "macro_errors.h"
#include "str_func.h"

static int fill_file_from_input(redirect_t redirect)
{
    int pipefd[2];
    char *line = NULL;
    size_t len = 0;
    char *to_comp = my_strcat_dup(redirect.name, "\n");

    if (to_comp == NULL || pipe(pipefd) == -1)
        return ERROR;
    fprintf(stdout, "? ");
    getline(&line, &len, stdin);

    while (my_strcmp(line, to_comp) != 0){
        fprintf(stdout, "? ");
        dprintf(pipefd[1], line);
        getline(&line, &len, stdin);
    }
    free(to_comp);
    free(line);
    close(pipefd[1]);
    return pipefd[0];
}

int set_fd_input(command_t *command)
{
    redirect_t redirect = command->redirect_in;

    command->fd_in = STDIN_FILENO;
    if (command->redirect_in.type == NO_REDIRECT)
        return SUCCESS;
    if (redirect.type == IN_1) {
        if ((command->fd_in = open(redirect.name, O_RDONLY)) < 0) {
            perror(redirect.name);
            return EXIT;
        }
    }
    if (redirect.type == IN_2) {
        if ((command->fd_in = fill_file_from_input(redirect)) < 0)
            return ERROR;
    }
    return SUCCESS;
}

int set_fd_output(command_t *command)
{
    if (command->redirect_out.type == OUT_1)
        command->fd_out = open(command->redirect_out.name,
        O_CREAT | O_WRONLY | O_TRUNC, 00644);
    if (command->redirect_out.type == OUT_2)
        command->fd_out = open(command->redirect_out.name,
        O_CREAT | O_WRONLY | O_APPEND, 00644);
    if (command->fd_out < 0) {
        perror(command->redirect_out.name);
        return ERROR;
    }
    return SUCCESS;
}
