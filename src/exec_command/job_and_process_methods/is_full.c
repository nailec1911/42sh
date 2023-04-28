/*
** EPITECH PROJECT, 2023
** job_and_process_methods
** File description:
** is_full
*/

#include "job_control.h"

bool is_full(job_stack *stack)
{
    if (stack->top == MAX_JOBS - 1)
        return true;
    return false;
}
