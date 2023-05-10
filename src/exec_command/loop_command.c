/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** loop_grocommand
*/

#include "mysh.h"
#include "macro_errors.h"
#include "exec_command.h"
#include "job_control.h"
#include "parser/ast.h"
#include <stdlib.h>

void display_list(job_list *list)
{
    for (job_list *tmp = list; tmp; tmp = tmp->next) {
        printf("[job id : %d ", tmp->job->job_id);
        for (int i = 0; i < tmp->job->nb_command; ++i) {
            printf("(args : %s)", tmp->job->tab_command[i].args[0]);
            printf("(pid : %d)", tmp->job->tab_command[i].pid);
        }
        printf("]->");
    }
    printf("\n");
}

static int loop_and_command(mysh_t *mysh, or_command_t *or_command)
{
    int res = 0;
    int exit = 0;
    int i = 0;

    do {
        mysh->last_status = 0;
        set_and_command(mysh, &(or_command->tab_and_command[i]));
        mysh->nb_current_job++;
        or_command->tab_and_command[i].job_id = mysh->nb_current_job;
        mysh->list = add_job_to_list(mysh->list,
                &or_command->tab_and_command[i]);
        res = exec_job(mysh, &or_command->tab_and_command[i]);
        or_command->tab_and_command = NULL;
        if (res == ERROR)
            return ERROR;
        if (res == EXIT)
            exit = EXIT;
        i += 1;
    } while (i < or_command->nb_and_command && mysh->last_status == SUCCESS);
    return exit;
}

static int loop_or_command(mysh_t *mysh, grocommand_t *grocommand)
{
    int res = 0;
    int exit = 0;
    int i = 0;

    do {
        mysh->last_status = SUCCESS;
        res = loop_and_command(mysh, &(grocommand->tab_or_command[i]));
        if (res == ERROR)
            return ERROR;
        if (res == EXIT)
            exit = EXIT;
        i += 1;
    } while ( i < grocommand->nb_or_command && mysh->last_status != SUCCESS);

    return exit;
}

int loop_grocommand(mysh_t *mysh, ast_t *ast)
{
    int res = 0;
    int exit = 0;

    for (int i = 0; i < ast->nb_grocommand; i += 1) {
        mysh->last_status = 0;
        res = loop_or_command(mysh, &(ast->tab_grocommands[i]));
        if (res == ERROR)
            return ERROR;
        if (res == EXIT)
            exit = EXIT;
    }

    return exit;
}
