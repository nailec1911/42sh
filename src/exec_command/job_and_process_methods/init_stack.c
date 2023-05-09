/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** init_stack
*/

#include "job_control.h"
#include "parser/ast.h"

job_stack *init_stack(job_stack *stack)
{
    stack->job = malloc(sizeof(and_command_t*) * MAX_JOBS);

    if (!stack->job || !stack)
        return NULL;
    for (int i = 0; i < MAX_JOBS; ++i)
        if (!(stack->job[i] = malloc(sizeof(and_command_t))))
            return NULL;
    stack->top = 0;
    return stack;
}
