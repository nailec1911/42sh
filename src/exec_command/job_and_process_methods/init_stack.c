/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** init_stack
*/

#include "job_control.h"

job_stack init_stack(job_stack stack)
{
    stack.job = malloc(sizeof(and_command_t*) * MAX_JOBS);
    stack.top = 0;
    return stack;
}
