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
#include <errno.h>

#include "color.h"
#include "macro_errors.h"
#include "str_func.h"
#include "mysh.h"
#include "builtins/env.h"

static char *get_git_branch(void)
{
    FILE *stream;
    char *buffer = malloc(1024);
    int i = 0;

    if (!buffer)
        return NULL;
    if (!(stream = popen("git rev-parse --abbrev-ref HEAD 2>/dev/null", "r")))
        return NULL;
    if (!(fgets(buffer, 1024, stream)))
        return 0x00000000;
    for (; buffer[i] && buffer[i] != ' '; ++i);
    buffer[i - 1] = 0;
    pclose(stream);
    return buffer;
}

static void
display_prompt(mysh_t *mysh,
        struct passwd *pw, char *git_branch, char *current_dir)
{
    printf(BLACK ERROR_B_COLOR " %d " TRUE_WHITE B_COLOR " %s"
            TRUE_WHITE B_COLOR" ~%s " BLACK BRANCH_B_COLOR " %s "
            NO_COLOR "\n", mysh->last_status, pw->pw_name,
            &current_dir[strlen(pw->pw_dir)], git_branch ? git_branch : "");
    printf("> ");
}

void init_prompt(mysh_t *mysh)
{
    struct passwd *pw;
    char current_dir[4096];
    char *git_branch = NULL;
    if (!isatty(SHELL_DESCRIPTOR))
        return;
    pw = getpwuid(getuid());
    getcwd(current_dir, sizeof(current_dir));
    git_branch = get_git_branch();
    display_prompt(mysh, pw, git_branch, current_dir);
    fflush(stdout);
    if (git_branch)
        free(git_branch);
}
