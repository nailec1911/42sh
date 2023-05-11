/*
** EPITECH PROJECT, 2023
** builtins
** File description:
** which
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <mysh.h>

#include "exec_command.h"
#include "parser/ast.h"
#include "macro_errors.h"

static char *tab[15] = {"cd",
                "exit",
                "env",
                "setenv",
                "unsetenv",
                "history",
                "alias",
                "unalias",
                "set",
                "unset",
                "fg",
                "which",
                "echo",
                "where",
                NULL};

static bool is_builin(char *s)
{
    for (int i = 0; tab[i]; ++i) {
        if (strcmp(s, tab[i]) == 0)
            return true;
    }
    return false;
}

int do_which(mysh_t *mysh, command_t *to_exec)
{
    char *path = "";
    if (!mysh || !to_exec)
        return SUCCESS;
    if (!to_exec->args[1]) {
        fprintf(stderr, "which: Too few arguments.\n");
        return SUCCESS;
    }
    for (int i = 1; to_exec->args[i]; ++i) {
        if (is_builin(to_exec->args[i])) {
            fprintf(stderr, "%s: shell built-in command.\n", to_exec->args[i]);
            continue;
        }
        to_exec->args[0] = strdup(to_exec->args[i]);
        if (get_path(mysh, &path, to_exec) != SUCCESS) {
            fprintf(stderr, "%s: Command not found.\n", to_exec->args[i]);
            continue;
        }
        printf("%s\n", path);
    }
    return SUCCESS;
}
