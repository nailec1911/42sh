/*
** EPITECH PROJECT, 2023
** JOB_CONTROL_H_
** File description:
** job_control
*/


#ifndef JOB_CONTROL_H_
    #define JOB_CONTROL_H_

    #include "parser/ast.h"
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>

    #define MAX_JOBS 1000

    typedef struct job_list {
        struct job_list *next;
        and_command_t *job;
    } job_list;

    typedef struct job_stack {
        short top;
        and_command_t **job;
    } job_stack;

    //job_list
    job_list *add_job_to_list(job_list *list, and_command_t* job);
    int wait_job(job_list *list, and_command_t *job);
    int get_job_id(job_list *list, pid_t pid);
    job_list *remove_job_from_list(job_list *list, int job_id);
    void display_job_status(and_command_t *job);
    void display_background(and_command_t *job);
    bool job_is_stoped(and_command_t *job);
    bool job_is_completed(and_command_t *job);
    int update_process_status(job_list *list, pid_t pid, int status);
    job_list *lookup_job(job_list *list, int *nb_job);
    pid_t get_last_job_pgid(job_list *list);

    // stack
    job_stack *init_stack(job_stack *stack);
    bool is_full(job_stack *stack);
    bool is_empty(job_stack *stack);
    void peek(job_stack stack);
    void push(job_stack *stack, and_command_t *job);
    and_command_t *pop(job_stack *stack);
    bool job_is_completed(and_command_t *job);
    bool job_is_stoped(and_command_t *job);
    and_command_t *get_job_from_id(job_list *list, int job_id);
    and_command_t *get_job_from_pid(job_list *list, pid_t pid);

#endif /* JOB_CONTROL_H_ */
