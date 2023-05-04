src/builtins/alias/init_alias.c:20:    mysh->alias.fd_alias_file = open(ALIASRC_FILE, O_CREAT |
src/builtins/alias/init_alias.c:22:    mysh->alias.fd_file = fopen(ALIASRC_FILE, "a+");
src/builtins/alias/init_alias.c:23:    if (mysh->alias.fd_file == NULL)
src/builtins/alias/init_alias.c:28:        mysh->alias.tab_file = NULL;
src/builtins/alias/init_alias.c:30:        mysh->alias.tab_file = file_to_tab(ALIASRC_FILE);
src/builtins/alias/init_alias.c:31:        if (mysh->alias.tab_file == NULL)
src/builtins/alias/builtins_alias.c:20:    if (mysh->alias.tab_file == NULL) {
src/builtins/alias/builtins_alias.c:21:        mysh->alias.tab_file = malloc(sizeof(char *) * 2);
src/builtins/alias/builtins_alias.c:22:        if (mysh->alias.tab_file == NULL)
src/builtins/alias/builtins_alias.c:24:        mysh->alias.tab_file[0] = input;
src/builtins/alias/builtins_alias.c:25:        mysh->alias.tab_file[1] = NULL;
src/builtins/alias/builtins_alias.c:26:        fprintf(mysh->alias.fd_file, "%s", mysh->alias.tab_file[0]);
src/builtins/alias/builtins_alias.c:28:        if (add_elem_tab_alias(&mysh->alias, input) == ERROR)
src/builtins/alias/builtins_alias.c:30:        l_tab = length_tab(mysh->alias.tab_file);
src/builtins/alias/builtins_alias.c:31:        fprintf(mysh->alias.fd_file, "%s", mysh->alias.tab_file[l_tab - 1]);
src/builtins/alias/builtins_alias.c:33:    fflush(mysh->alias.fd_file);
src/builtins/alias/builtins_alias.c:41:        if (mysh->alias.tab_file == NULL)
src/builtins/alias/builtins_alias.c:43:        return display_alias(mysh->alias, to_exec.fd_out);
src/builtins/alias/builtins_alias.c:46:        if (mysh->alias.tab_file == NULL)
src/builtins/alias/builtins_alias.c:49:        (mysh->alias, to_exec.args[1], to_exec.fd_out);
src/builtins/alias/builtins_alias.c:53:            mysh->last_status = 1;
src/builtins/alias/builtins_alias.c:80:    if (mysh->alias.tab_file == NULL)
src/builtins/alias/builtins_alias.c:82:    for (int i = 0; mysh->alias.tab_file[i] != NULL; i += 1) {
src/builtins/alias/builtins_alias.c:84:        (mysh->alias.tab_file[i], " \n");
src/builtins/cd/cd.c:24:        mysh->last_status = errno;
src/builtins/cd/cd.c:59:    if (mysh->command[1] != NULL && mysh->command[2] != NULL) {
src/builtins/cd/cd.c:61:        mysh->last_status = 1;
src/builtins/cd/cd.c:69:        display_error_chdir(errno, mysh->command[1]);
src/builtins/cd/cd.c:70:        mysh->last_status = 1;
src/builtins/cd/get_path_to_go.c:22:        mysh->last_status = 1;
src/builtins/cd/get_path_to_go.c:25:    if (mysh->command[1] == NULL)
src/builtins/cd/get_path_to_go.c:28:    my_strcat_dup(home_path, mysh->command[1] + 1)) == NULL) {
src/builtins/cd/get_path_to_go.c:29:        mysh->last_status = FAILURE;
src/builtins/cd/get_path_to_go.c:37:    char *path = mysh->command[1];
src/builtins/cd/get_path_to_go.c:39:    if (mysh->command[1] == NULL || mysh->command[1][0] == '~')
src/builtins/cd/get_path_to_go.c:41:    if (mysh->command[1][0] == '-' && mysh->command[1][1] == '\0')
src/builtins/cd/get_path_to_go.c:45:        mysh->last_status = 1;
src/builtins/env/free_env.c:18:    for (int i = 0; mysh->env[i]; ++i)
src/builtins/env/free_env.c:19:        free(mysh->env[i]);
src/builtins/env/free_env.c:20:    free(mysh->env);
src/builtins/env/free_env.c:21:    fclose(mysh->history.fd_file);
src/builtins/env/free_env.c:22:    close(mysh->history.fd_history_file);
src/builtins/env/free_env.c:23:    fclose(mysh->alias.fd_file);
src/builtins/env/free_env.c:24:    close(mysh->alias.fd_alias_file);
src/builtins/env/free_env.c:25:    free(mysh->history.command);
src/builtins/env/free_env.c:26:    if (mysh->alias.tab_file != NULL) {
src/builtins/env/free_env.c:27:        free_array(mysh->alias.tab_file);
src/builtins/env/free_env.c:29:    if (mysh->history.tab_file != NULL) {
src/builtins/env/free_env.c:30:        free_array(mysh->history.tab_file);
src/builtins/env/free_env.c:32:    if (mysh->history.tab_hist != NULL) {
src/builtins/env/free_env.c:33:        free_tab_hist(mysh->history.tab_hist);
src/builtins/env/get_env_var.c:19:    for (int i = 0; mysh->env[i] != NULL; ++i)
src/builtins/env/get_env_var.c:20:        if (strncmp(var, mysh->env[i], len_var) == SUCCESS)
src/builtins/env/get_env_var.c:21:            return mysh->env[i] + len_var;
src/builtins/env/modify_env_var.c:69:    for (; mysh->env[i] != NULL; ++i) {
src/builtins/env/modify_env_var.c:70:        if (strncmp(mysh->env[i], to_change, len) == 0)
src/builtins/env/modify_env_var.c:71:            return edit_var(to_change, new_value, &(mysh->env[i]));
src/builtins/env/modify_env_var.c:74:        if ((mysh->env = init_env(to_change, new_value)) == NULL)
src/builtins/env/modify_env_var.c:78:    if ((mysh->env = add_var(mysh->env, to_change, new_value, i)) == NULL)
src/builtins/env/setenv.c:33:        mysh->last_status = 1;
src/builtins/env/setenv.c:36:    if (mysh->command[1] == NULL || mysh->command[1][0] == '\0')
src/builtins/env/setenv.c:41:    mysh->last_status = 0;
src/builtins/env/unsetenv.c:52:        mysh->last_status = 1;
src/builtins/env/unsetenv.c:56:        idx = get_var_idx(mysh->env, to_exec.args[i]);
src/builtins/env/unsetenv.c:58:            mysh->env = remove_from_env(mysh->env, idx);
src/builtins/env/env.c:20:        mysh->last_status = 127;
src/builtins/env/env.c:23:    for (int i = 0; mysh->env[i]; ++i) {
src/builtins/env/env.c:24:        dprintf(to_exec.fd_out, "%s\n", mysh->env[i]);
src/builtins/env/env.c:26:    mysh->last_status = 0;
src/builtins/history/check_last_command.c:25:    int l_tab = length_tab_hist(mysh->history.tab_hist);
src/builtins/history/check_last_command.c:26:    free(mysh->history.tab_hist[l_tab - 1]->num);
src/builtins/history/check_last_command.c:27:    free(mysh->history.tab_hist[l_tab - 1]->time);
src/builtins/history/check_last_command.c:28:    free(mysh->history.tab_hist[l_tab - 1]->command);
src/builtins/history/check_last_command.c:29:    mysh->history.tab_hist[l_tab - 1]->num =
src/builtins/history/check_last_command.c:30:    num_to_str(mysh->history.num_command);
src/builtins/history/check_last_command.c:31:    mysh->history.tab_hist[l_tab - 1]->time = create_time_line();
src/builtins/history/check_last_command.c:32:    mysh->history.tab_hist[l_tab - 1]->command = strdup(input);
src/builtins/history/check_last_command.c:33:    write_in_file(mysh->history.tab_hist, mysh->history.fd_file);
src/builtins/history/check_last_command.c:39:    if (add_elem_tab(&(mysh->history), input,
src/builtins/history/check_last_command.c:40:    mysh->history.num_command) == ERROR)
src/builtins/history/check_last_command.c:42:    write_in_file(mysh->history.tab_hist, mysh->history.fd_file);
src/builtins/history/check_last_command.c:48:    int l_tab = length_tab_hist(mysh->history.tab_hist);
src/builtins/history/check_last_command.c:49:    if (strcmp(input,mysh->history.tab_hist[l_tab - 1]->command) == 0) {
src/builtins/history/check_last_command.c:58:    if (mysh->history.tab_hist == NULL) {
src/builtins/history/check_last_command.c:59:        mysh->history.tab_hist = malloc(sizeof(tab_hist_t *) * 2);
src/builtins/history/check_last_command.c:60:        mysh->history.tab_hist[0] = malloc(sizeof(tab_hist_t));
src/builtins/history/check_last_command.c:61:        mysh->history.tab_hist[0]->num = num_to_str(mysh->history.num_command);
src/builtins/history/check_last_command.c:62:        mysh->history.tab_hist[0]->time = create_time_line();
src/builtins/history/check_last_command.c:63:        mysh->history.tab_hist[0]->command = strdup(input);
src/builtins/history/check_last_command.c:64:        mysh->history.tab_hist[1] = NULL;
src/builtins/history/check_last_command.c:65:        write_in_file(mysh->history.tab_hist, mysh->history.fd_file);
src/builtins/history/exclamation_mark.c:21:            mysh->last_status = 1;
src/builtins/history/exclamation_mark.c:22:            mysh->display_line = false;
src/builtins/history/exclamation_mark.c:30:        mysh->last_status = 1;
src/builtins/history/exclamation_mark.c:31:        mysh->display_line = false;
src/builtins/history/exclamation_mark.c:45:        mysh->last_status = 1;
src/builtins/history/functions_history.c:25:    if (ftruncate(mysh->history.fd_history_file, 0) == -1) {
src/builtins/history/functions_history.c:30:    mysh->history.num_command += 1;
src/builtins/history/functions_history.c:31:    fflush(mysh->history.fd_file);
src/builtins/history/functions_history.c:39:    mysh->history.num_command += 1;
src/builtins/history/functions_history.c:46:    mysh->history.num_command = 0;
src/builtins/history/functions_history.c:47:    mysh->history.fd_history_file = open(HISTORY_FILE, O_CREAT |
src/builtins/history/functions_history.c:49:    mysh->history.fd_file = fdopen(mysh->history.fd_history_file, "a+");
src/builtins/history/functions_history.c:53:        mysh->history.num_command = 1;
src/builtins/history/functions_history.c:54:        mysh->history.tab_file = NULL;
src/builtins/history/functions_history.c:55:        mysh->history.tab_hist = NULL;
src/builtins/history/functions_history.c:73:        mysh->history.tab_hist[*i] = malloc(sizeof(tab_hist_t));
src/builtins/history/functions_history.c:74:        mysh->history.tab_hist[*i]->num = num_to_str(atoi(tab[0]));
src/builtins/history/functions_history.c:75:        mysh->history.tab_hist[*i]->time = strdup(tab[1]);
src/builtins/history/functions_history.c:77:        mysh->history.tab_hist[*i]->command = my_strcat_dup(command, "\n");
src/builtins/history/functions_history.c:78:        mysh->history.num_command = atoi(tab[0]);
src/builtins/history/functions_history.c:95:    if ((mysh->history.tab_hist =
src/builtins/history/functions_history.c:98:    mysh->history.tab_hist[nb_line] = NULL;
src/builtins/history/search_command.c:20:    for (int i = 0; mysh->history.tab_hist[i] != NULL; i += 1) {
src/builtins/history/search_command.c:21:        num_command = atoi(mysh->history.tab_hist[i]->num);
src/builtins/history/search_command.c:23:            command = strdup(mysh->history.tab_hist[i]->command);
src/builtins/history/search_command.c:35:    int len_tab_hist = length_tab_hist(mysh->history.tab_hist);
src/builtins/history/search_command.c:39:        (mysh->history.tab_hist[i]->command, "\n");
src/builtins/history/builtins_history.c:16:    int l_tab = length_tab_hist(mysh->history.tab_hist);
src/builtins/history/builtins_history.c:17:    tab_hist_t **to_free = mysh->history.tab_hist;
src/builtins/history/builtins_history.c:23:    tab[0]->num = strdup(mysh->history.tab_hist[l_tab - 1]->num);
src/builtins/history/builtins_history.c:24:    tab[0]->time = strdup(mysh->history.tab_hist[l_tab - 1]->time);
src/builtins/history/builtins_history.c:25:    tab[0]->command = strdup(mysh->history.tab_hist[l_tab - 1]->command);
src/builtins/history/builtins_history.c:27:    mysh->history.tab_hist = tab;
src/builtins/history/builtins_history.c:53:    char *num = num_to_str(mysh->history.num_command);
src/builtins/history/builtins_history.c:67:        return display_history(mysh->history.tab_hist, to_exec.fd_out, mysh);
src/builtins/history/builtins_history.c:72:        return opt_sort(mysh->history.tab_hist, to_exec.fd_out);
src/builtins/history/builtins_history.c:74:        return opt_without_info(mysh->history.tab_hist, to_exec.fd_out);
src/builtins/history/builtins_history.c:76:        return display_history(mysh->history.tab_hist, to_exec.fd_out, mysh);
src/builtins/history/builtins_history.c:79:        mysh->last_status = 1;
src/builtins/unalias/remove_alias.c:18:    for (int i = 0; mysh->alias.tab_file[i] != NULL; i += 1) {
src/builtins/unalias/remove_alias.c:19:        fprintf(mysh->alias.fd_file, "%s", mysh->alias.tab_file[i]);
src/builtins/unalias/remove_alias.c:21:    fflush(mysh->alias.fd_file);
src/builtins/unalias/remove_alias.c:44:    for (int i = 0; mysh->alias.tab_file[i] != NULL; i += 1) {
src/builtins/unalias/remove_alias.c:46:        (mysh->alias.tab_file[i], " \n");
src/builtins/unalias/remove_alias.c:48:            new_tab[index] = strdup(mysh->alias.tab_file[i]);
src/builtins/unalias/remove_alias.c:51:            free(mysh->alias.tab_file[i]);
src/builtins/unalias/remove_alias.c:55:    free(mysh->alias.tab_file);
src/builtins/unalias/remove_alias.c:65:    l_tab = length_tab(mysh->alias.tab_file);
src/builtins/unalias/remove_alias.c:66:    nb_elem = nb_elem_to_remove(mysh->alias.tab_file, command);
src/builtins/unalias/remove_alias.c:70:    mysh->alias.tab_file = fill_tab_without_alias(mysh, new_tab, command);
src/builtins/unalias/remove_alias.c:71:    if (mysh->alias.tab_file == NULL)
src/builtins/unalias/remove_alias.c:82:        mysh->last_status = 1;
src/builtins/unalias/remove_alias.c:85:    if (mysh->alias.tab_file == NULL || mysh->alias.tab_file[0] == NULL)
src/builtins/unalias/remove_alias.c:91:    if (ftruncate(mysh->alias.fd_alias_file, 0) == -1) {
src/builtins/exit.c:18:        mysh->last_status = 1;
src/builtins/fg/fg.c:20:    job_list *tmp = mysh->list;
src/builtins/fg/fg.c:26:    position = get_job_id(mysh->list, pid);
src/exec_command/exec_pipes.c:42:        exit(mysh->last_status);
src/exec_command/loop_command.c:22:        mysh->last_status = 0;
src/exec_command/loop_command.c:24:        mysh->nb_current_job++;
src/exec_command/loop_command.c:25:        or_command->tab_and_command[i].job_id = mysh->nb_current_job;
src/exec_command/loop_command.c:26:        mysh->list = add_job_to_list(mysh->list, &or_command->tab_and_command[i]);
src/exec_command/loop_command.c:33:    } while (i < or_command->nb_and_command && mysh->last_status == SUCCESS);
src/exec_command/loop_command.c:45:        mysh->last_status = SUCCESS;
src/exec_command/loop_command.c:52:    } while ( i < grocommand->nb_or_command&& mysh->last_status != SUCCESS);
src/exec_command/loop_command.c:62:    for (int i = 0; i < mysh->ast.nb_grocommand; i += 1) {
src/exec_command/loop_command.c:63:        mysh->last_status = 0;
src/exec_command/loop_command.c:64:        res = loop_or_command(mysh, &(mysh->ast.tab_grocommands[i]));
src/exec_command/exec_job.c:79:            tcsetpgrp(mysh->shell_descriptor, job->pgid);
src/exec_command/exec_job.c:80:            status = wait_job(mysh->list, job);
src/exec_command/exec_job.c:82:            tcsetpgrp(mysh->shell_descriptor, getpid());
src/exec_command/exec_job.c:130:    loopkup_job(mysh->list, &mysh->nb_current_job);
src/exec_command/exec_job.c:144:        mysh->list = remove_job_from_list(mysh->list, job->job_id);
src/exec_command/exec_job.c:145:        mysh->nb_current_job--;
src/exec_command/exec_command.c:47:        mysh->last_status = status;
src/exec_command/exec_command.c:71:    mysh->command = to_exec.args;
src/exec_command/exec_command.c:77:        fprintf(stderr, "%s: Command not found.\n", mysh->command[0]);
src/exec_command/exec_command.c:78:        mysh->last_status = 1;
src/handle_input/get_path.c:49:    if ((*path = strdup(mysh->command[0])) == NULL)
src/handle_input/get_path.c:52:        if (access(mysh->command[0], F_OK) == 0)
src/handle_input/handle_input.c:19:    mysh->display_line = false;
src/handle_input/handle_input.c:39:            mysh->last_status = ERROR;
src/handle_input/handle_input.c:44:            mysh->last_status = FAILURE;
src/handle_input/handle_input.c:53:    int res = create_ast(list_token, &(mysh->ast));
src/handle_input/handle_input.c:56:        free_ast(mysh->ast);
src/handle_input/handle_input.c:57:        mysh->last_status = 1;
src/handle_input/handle_input.c:62:        mysh->last_status = ERROR;
src/handle_input/handle_input.c:72:    if (mysh->last_status == 1) {
src/handle_input/handle_input.c:80:    if ((res = set_all_ast(&(mysh->ast))) != SUCCESS) {
src/handle_input/handle_input.c:81:        mysh->last_status = res;
src/handle_input/loop_exclamation_mark.c:57:    mysh->display_line = true;
src/handle_input/loop_exclamation_mark.c:74:    && mysh->last_status != 1; i += 1) {
src/handle_input/tokens_to_history.c:54:    if (mysh->display_line) {
src/user_input/arrows_func.c:18:    read(STDIN_FILENO, &mysh->ch, 1);
src/user_input/arrows_func.c:19:    if (mysh->ch == 91) {
src/user_input/arrows_func.c:20:        read(STDIN_FILENO, &mysh->ch, 1);
src/user_input/arrows_func.c:23:    if (mysh->ch == 51) {
src/user_input/arrows_func.c:24:        read(STDIN_FILENO, &mysh->ch, 1);
src/user_input/choose_arrow.c:33:    if (mysh->history.tab_hist == NULL)
src/user_input/choose_arrow.c:35:    if (mysh->ind_history > 0)
src/user_input/choose_arrow.c:36:        mysh->ind_history -= 1;
src/user_input/choose_arrow.c:39:    line = strcpy(line, mysh->history.tab_hist[mysh->ind_history]->command);
src/user_input/choose_arrow.c:54:    mysh->ind_history += 1;
src/user_input/choose_arrow.c:55:    if (mysh->ind_history == mysh->ind_init)
src/user_input/choose_arrow.c:57:    if (mysh->ind_history > length_tab_hist(mysh->history.tab_hist) - 1) {
src/user_input/choose_arrow.c:58:        mysh->ind_history -= 1;
src/user_input/choose_arrow.c:63:    line = strcpy(line, mysh->history.tab_hist[mysh->ind_history]->command);
src/user_input/choose_arrow.c:77:    switch (mysh->ch) {
src/user_input/choose_arrow.c:91:            ctrl_functions(index, length, mysh->ch);
src/user_input/get_input.c:80:    switch (mysh->ch) {
src/user_input/get_input.c:90:            line = fill_string(line, mysh->ch, index, length);
src/mysh.c:39:    loopkup_job(mysh->list, &mysh->nb_current_job);
src/mysh.c:40:    mysh->to_return = mysh->last_status;
src/mysh.c:41:    mysh->last_status = 0;
src/mysh.c:51:    //free_ast(mysh->ast);
src/mysh.c:57:    mysh->tty = true;
src/mysh.c:62:    mysh->shell_pgid = getpid();
src/mysh.c:63:    mysh->shell_descriptor = STDIN_FILENO;
src/mysh.c:64:    setpgid(mysh->shell_pgid, mysh->shell_pgid);
src/mysh.c:65:    tcsetpgrp(mysh->shell_descriptor, mysh->shell_pgid);
src/mysh.c:70:    mysh->list = NULL;
src/mysh.c:73:    if ((mysh->env = init_mysh_env(env)) == NULL)
tests/test_function.c:22:    res = create_ast(list_token, &(mysh->ast));
tests/test_function.c:24:        mysh->last_status = res;
tests/test_function.c:28:    res = set_all_ast(&(mysh->ast));
tests/test_function.c:30:        mysh->last_status = res;
