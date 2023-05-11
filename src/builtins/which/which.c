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

int do_which(mysh_t *mysh, command_t *c)
{
    char *path = "";
    if (!mysh || !c)
        return SUCCESS;
    if (!c->args[1]) {
        fprintf(stderr, "which: Too few arguments.\n");
        return SUCCESS;
    }
    for (int i = 1; c->args[i]; ++i) {
        if (is_builin(c->args[i])) {
            dprintf(c->fd_out, "%s: shell built-in command.\n", c->args[i]);
            continue;
        }
        c->args[0] = strdup(c->args[i]);
        if (get_path(mysh, &path, c) != SUCCESS) {
            dprintf(c->fd_out, "%s: Command not found.\n", c->args[i]);
            continue;
        }
        dprintf(c->fd_out, "%s\n", path);
    }
    return SUCCESS;
}
