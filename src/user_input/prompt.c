/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include "color.h"
#include "macro_errors.h"
#include "str_func.h"
#include "mysh.h"
#include "builtins/env.h"

static char *get_git_branch(void)
{
    FILE *stream;
    char *buffer = malloc(1024);

    if (!buffer)
        return NULL;
    if (!(stream = popen("git rev-parse --abbrev-ref HEAD", "r")))
        return NULL;
    int ch = 0;
    size_t bytes_read = 0;
    while ((ch = fgetc(stream)) != EOF)
        buffer[bytes_read++] = ch;
    buffer[bytes_read - 1] = 0;
    pclose(stream);
    return buffer;
}

void init_prompt(mysh_t *mysh)
{
    struct passwd *pw;
    char current_dir[4096];
    char *git_branch = malloc(1024);
    if (!isatty(mysh->shell_descriptor))
        return;
    pw = getpwuid(getuid());
    getcwd(current_dir, sizeof(current_dir));
    git_branch = get_git_branch();
    if (git_branch)
        printf(BLACK ERROR_B_COLOR " %d " TRUE_WHITE B_COLOR " %s"
                TRUE_WHITE B_COLOR" ~%s " BLACK BRANCH_B_COLOR " %s "
                NO_COLOR " ", mysh->last_status, pw->pw_name,
                &current_dir[strlen(pw->pw_dir)], git_branch);
    else
        printf(BLACK ERROR_B_COLOR " %d " TRUE_WHITE B_COLOR " %s"
                TRUE_WHITE B_COLOR" ~%s " BLACK BRANCH_B_COLOR " %s " NO_COLOR
                " ", mysh->last_status, pw->pw_name,
                &current_dir[strlen(pw->pw_dir)], git_branch);
    fflush(stdout);
    free(git_branch);
}
