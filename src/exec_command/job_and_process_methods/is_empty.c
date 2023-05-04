/*
** EPITECH PROJECT, 2023
** job_and_process_methods
** File description:
** is_empty
*/

#include "job_control.h"

bool is_empty(job_stack *stack)
{
    if (stack->top == 0)
        return true;
    return false;
}
