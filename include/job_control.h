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
    /*
    typedef enum status {
        RUNNING,
        DONE,
        SUSPENDED,
        CONTINUED,
        TERMINATED
    } status;

    typedef enum mode {
        FOREGROUND,
        BACKGROUND
    } mode;

    typedef struct process {
        char **     args;
        redirect_t  redirect_in;
        redirect_t  redirect_out;
        int         fd_in;
        int         fd_out;
        pid_t       pid;
        bool        is_builtin;
        status      process_state;
        struct      process *next;
    } process;

    typedef struct job {
        int     job_id;
        pid_t   pgid;
        mode    job_mode;
        process *head;
        struct  job *next;
    } job;

    job *add_job(job *j, and_command_t *command_tab, int job_id);
    process *add_process(process *p, command_t *command);
    int exec_job(job *j);
    int wait_job(job *j);
    */

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
    job_list *remove_job_from_list(job_list *list, pid_t pid);
    void display_job_status(and_command_t *job);
    bool job_is_stoped(and_command_t *job);
    bool job_is_completed(and_command_t *job);
    int update_process_status(job_list *list, pid_t pid, int status);
    void loopkup_job(job_list *list, int *nb_job);

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

#endif /* JOB_CONTROL_H_ */
