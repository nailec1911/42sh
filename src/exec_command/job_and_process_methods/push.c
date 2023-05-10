/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** push
*/

#include "job_control.h"
#include "parser/ast.h"

void push(job_stack *stack, and_command_t *job)
{
    if (!stack || !job)
        return;
    if (is_full(stack))
        return;
    stack->job[stack->top] = job;
    stack->top++;
}
