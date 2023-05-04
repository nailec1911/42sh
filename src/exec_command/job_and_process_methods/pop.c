/*
** EPITECH PROJECT, 2023
** job_and_process_methods
** File description:
** pop
*/

#include "job_control.h"

and_command_t *pop(job_stack *stack)
{
    if (is_empty(stack))
        return NULL;
    return stack->job[stack->top--];
}
