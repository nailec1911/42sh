##
## EPITECH PROJECT, 2023
## mysh
## File description:
## Makefile
##

SOURCE_DIR	=	src/

SRC	=	mysh.c		\
		get_input.c	\
		handle_input/parsing/parse_input.c			\
		handle_input/parsing/set_all_ast.c			\
		handle_input/parsing/free_ast.c				\
		handle_input/parsing/lexer/lexer.c					\
		handle_input/parsing/lexer/lexer_mod.c				\
		handle_input/parsing/lexer/single_char_tokens.c		\
		handle_input/parsing/lexer/single_mul_char_tokens.c	\
		handle_input/parsing/lexer/quoted_tokens.c	\
		handle_input/parsing/lexer/multiple_char_tokens.c	\
		handle_input/parsing/parser/create_ast.c			\
		handle_input/parsing/parser/token_is_type.c		\
		handle_input/parsing/parser/get_grocommand.c		\
		handle_input/parsing/parser/get_or_command.c		\
		handle_input/parsing/parser/get_and_command.c		\
		handle_input/parsing/parser/get_command.c			\
		handle_input/get_path.c					\
		handle_input/set_fd_for_exec.c				\
		exec_command/loop_command.c		\
		exec_command/magic_quote/set_magic_quote.c		\
		exec_command/magic_quote/get_res_command.c		\
		exec_command/magic_quote/set_new_tab.c		\
		exec_command/exec_pipes.c	\
		exec_command/exec_command.c		\
		exec_command/exec_builtins.c	\
		exec_command/handle_errors.c	\
		str_func/my_strlen.c		\
		str_func/is_in.c			\
		str_func/my_strcat_dup.c	\
		str_func/my_strcat_with_char.c	\
		str_func/my_strcmp.c		\
		str_func/my_str_dup.c		\
		str_func/my_strncmp.c		\
		str_func/my_putstr.c		\
		str_func/free_array.c		\
		str_func/str_is_alphanum.c	\
		str_func/input_to_array.c	\
		str_func/my_strstrlen.c	\
		builtins/cd/cd.c				\
		builtins/cd/get_path_to_go.c 	\
		builtins/env/setenv.c			\
		builtins/env/unsetenv.c			\
		builtins/env/get_env_var.c		\
		builtins/env/modify_env_var.c	\
		builtins/env/init_mysh_env.c	\
		builtins/env/free_env.c		\
		builtins/env/env.c			\
		builtins/exit.c

SRC_MAIN	=	src/main.c

OBJ	=	$(addprefix $(SOURCE_DIR), $(SRC:.c=.o)) $(SRC_MAIN:.c=.o)

TO_TEST	=	tests/test_lexer.c	\
			tests/test_parser.c	\
			tests/test_builtin_cd.c		\
			tests/test_env_handling.c		\
			tests/test_builtins_env.c	\
			tests/test_strcat.c			\
			tests/test_strcmp.c			\
			tests/test_handle_error.c	\
			tests/test_input_to_array.c	\
			tests/test_get_path.c	\
			tests/test_full_sh.c	\
			tests/test_full_sh_operators.c

OBJ_TEST = $(addprefix $(SOURCE_DIR), $(SRC:.c=.o)) $(TO_TEST:.c=.o)

CPPFLAGS	=	-I./include

CFLAGS	=	-W -Wall -Wextra

LDLIBS	=	-lcriterion -lgcov

NAME	=	42sh

NAME_TESTS	=	unit_tests

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CPPFLAGS) $(LFLAGS)

tests_run: CPPFLAGS += --coverage
tests_run: fclean $(OBJ_TEST)
	gcc -o $(NAME_TESTS) $(OBJ_TEST) $(LDLIBS)
	-./$(NAME_TESTS)

debug: fclean
debug: CFLAGS += -ggdb3
debug: $(NAME)

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_TEST)
	find . -name "*~" -delete
	find . -name '#'*'#' -delete
	find . -name "*.gc*" -delete

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests*

re: fclean all

.PHONY: all tests_run clean fclean re debug
