##
## EPITECH PROJECT, 2023
## mysh
## File description:
## Makefile
##

SOURCE_DIR	=	src/

SRC	=	mysh.c		\
		loop_sh.c 	\
		handle_input/handle_input.c			\
		handle_input/error_in_token_list.c			\
		handle_input/tokens_to_history.c			\
		handle_input/exclamation_mark.c		\
		handle_input/loop_for_aliases.c				\
		handle_input/remove_inhibitors.c	\
		handle_input/quote_and_inhib.c	\
		handle_input/replace_var.c	\
		handle_input/parsing/set_all_ast.c			\
		handle_input/parsing/free_ast.c				\
		handle_input/parsing/lexer/lexer.c					\
		handle_input/parsing/lexer/peek_get.c				\
		handle_input/parsing/lexer/single_char_tokens.c		\
		handle_input/parsing/lexer/single_mul_char_tokens.c	\
		handle_input/parsing/lexer/quoted_tokens.c	\
		handle_input/parsing/lexer/multiple_char_tokens.c	\
		handle_input/parsing/parser/create_ast.c			\
		handle_input/parsing/parser/get_grocommand.c		\
		handle_input/parsing/parser/get_or_command.c		\
		handle_input/parsing/parser/get_and_command.c		\
		handle_input/parsing/parser/get_command.c			\
		handle_input/parsing/parser/get_ast_parenthesis.c	\
		handle_input/parsing/parser/error_in_command.c	\
		handle_input/get_path.c					\
		handle_input/set_fd_for_exec.c				\
		exec_command/globbins/globbins.c 			\
		exec_command/loop_command.c		\
		exec_command/magic_quote/set_magic_quote.c		\
		exec_command/magic_quote/get_res_command.c		\
		exec_command/magic_quote/file_stream_to_tab.c		\
		exec_command/exec_parenthesis/exec_parenthesis.c	\
		exec_command/set_and_command.c	\
		exec_command/exec_process.c	\
		exec_command/exec_builtins.c	\
		exec_command/handle_errors.c	\
		exec_command/exec_job.c 		\
		exec_command/wait_job.c	\
		exec_command/display_error_exec.c	\
		exec_command/job_and_process_methods/add_job_to_list.c 		\
		exec_command/job_and_process_methods/init_stack.c 		\
		exec_command/job_and_process_methods/is_empty.c 		\
		exec_command/job_and_process_methods/is_full.c 		\
		exec_command/job_and_process_methods/pop.c 		\
		exec_command/job_and_process_methods/push.c 		\
		exec_command/job_and_process_methods/remove_job_from_list.c 	\
		exec_command/job_and_process_methods/get_job_from_id.c 	\
		exec_command/job_and_process_methods/get_job_id.c 		\
		exec_command/job_and_process_methods/update_process_status.c 		\
		exec_command/job_and_process_methods/get_job_status.c 		\
		exec_command/job_and_process_methods/get_job_from_pid.c 		\
		exec_command/job_and_process_methods/display_job.c 		\
		str_func/is_in.c			\
		str_func/is_num.c			\
		str_func/my_strcat_dup.c	\
		str_func/my_strcat_with_char.c	\
		str_func/free_array.c		\
		str_func/str_is_alphanum.c	\
		str_func/my_strstrlen.c	\
		str_func/insert_array_in_array.c	\
		str_func/count_word.c 				\
		str_func/my_str_to_word_array.c 	\
		str_func/readfile.c 				\
		str_func/readfile_from_stream.c 				\
		user_input/arrows_func.c	\
		user_input/prompt.c	\
		user_input/get_input_line.c	\
		user_input/change_target_tab.c	\
		user_input/manage_enter_function.c	\
		user_input/get_input.c	\
		user_input/line_parsing.c	\
		user_input/ctrl_d_function.c	\
		user_input/display_spaces_comp.c	\
		user_input/tab_function.c	\
		user_input/set_terminal.c	\
		user_input/remove_functions.c	\
		user_input/ctrl_functions.c	\
		user_input/choose_arrow.c	\
		builtins/alias/init_alias.c\
		builtins/alias/builtins_alias.c\
		builtins/alias/is_alias.c\
		builtins/alias/remake_input.c\
		builtins/alias/display_alias.c\
		builtins/unalias/remove_alias.c\
		builtins/history/functions_history.c\
		builtins/history/exclamation_mark.c\
		builtins/history/remove_first_char.c\
		builtins/history/search_command.c\
		builtins/history/builtins_history.c\
		builtins/history/display_history.c\
		builtins/history/load_file_history.c\
		builtins/history/clean_str.c\
		builtins/history/search_env_var.c\
		builtins/history/add_elem_tab.c\
		builtins/history/combine_flags.c\
		builtins/history/check_last_command.c\
		builtins/history/usefull_function_history.c\
		builtins/history/num_to_str.c\
		builtins/history/file_to_tab.c\
		builtins/cd/cd.c				\
		builtins/cd/get_path_to_go.c 	\
		builtins/env/setenv.c			\
		builtins/env/unsetenv.c			\
		builtins/env/find_in_env.c			\
		builtins/env/get_env_var.c		\
		builtins/env/modify_env_var.c	\
		builtins/env/init_mysh_env.c	\
		builtins/env/free_env.c		\
		builtins/env/env.c			\
		builtins/exit.c				\
		builtins/vars/vars.c		\
		builtins/vars/set_var.c 	\
		builtins/vars/vars_utils.c 	\
		builtins/vars/unset_var.c 	\
		builtins/vars/recreate_args.c	\
		builtins/fg/fg.c   			\
		builtins/fg/fg_no_args.c   			\
		builtins/fg/fg_with_jid.c   			\
		builtins/fg/fg_with_pid.c   			\
		builtins/fg/send_cont.c 				\
		builtins/which/which.c

SRC_MAIN	=	src/main.c

OBJ	=	$(addprefix $(SOURCE_DIR), $(SRC:.c=.o)) $(SRC_MAIN:.c=.o)

TO_TEST	=	tests/test_function.c	\
			tests/test_lexer.c	\
			tests/test_parser.c	\
			tests/test_var.c	\
			tests/test_builtin_cd.c		\
			tests/test_env_handling.c		\
			tests/test_builtins_env.c	\
			tests/test_strcat.c			\
			tests/test_is_alpha_num.c			\
			tests/test_handle_error.c	\
			tests/test_str_to_array.c	\
			tests/test_get_path.c	\
			tests/test_globing.c	\
			tests/test_full_sh.c	\
			tests/test_full_sh_operators.c\
			tests/create_history.c \
			tests/test_history.c\
			tests/test_function_divers.c

OBJ_TEST = $(addprefix $(SOURCE_DIR), $(SRC:.c=.o)) $(TO_TEST:.c=.o)

CPPFLAGS	=	-I./include

CFLAGS	=	-W -Wall -Wextra

LDLIBS	=	-lcriterion -lgcov

NAME	=	42sh

NAME_TESTS	=	unit_tests

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

tests_run: CPPFLAGS += --coverage
tests_run: fclean $(OBJ_TEST)
	rm -f tests/.42sh*
	rm -f .42sh*
	gcc -o $(NAME_TESTS) $(OBJ_TEST) $(LDLIBS)
	-./$(NAME_TESTS)

debug: fclean
debug: CFLAGS += -ggdb3
debug: $(NAME)

clean:
	rm -f $(OBJ_TEST)
	find . -name "*.o" -delete
	find . -name "*~" -delete
	find . -name '#'*'#' -delete
	find . -name "*.gc*" -delete
	find . -name "vgcore.*" -delete

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests*

re: fclean all

.PHONY: all tests_run clean fclean re debug
