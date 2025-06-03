NAME =			minishell
CC =			cc
CFLAGS =		-Wall -Wextra -Werror -g
LDFLAGS =		-L./Libft -lft -lreadline -lncurses 

INC_DIR =		./includes
# TODO: Just for testing !!!
TEST_DIR =		./test
LIBFT_DIR =		./Libft
SRC_DIR =		./srcs
LEXER_DIR =		$(SRC_DIR)/lexer
PARSING_DIR =	$(SRC_DIR)/parsing
ENV_DIR =		$(SRC_DIR)/env
SIG_DIR =		$(SRC_DIR)/signals
AST_DIR =		$(SRC_DIR)/ast
EXEC_DIR =		$(SRC_DIR)/execution
EXECU_DIR =		$(EXEC_DIR)/utils
EXPAND_DIR =	$(SRC_DIR)/expansion
BUILT_DIR =		$(EXEC_DIR)/builtins
UTILS_DIR = 	$(SRC_DIR)/utils
CLEANUP_DIR = 	$(SRC_DIR)/cleanup
# TODO: Just for debug !!!
DEBUG_DIR =		$(SRC_DIR)/debug
INCLUDES =		-I${INC_DIR} -I./Libft/includes
LIBFT =			$(LIBFT_DIR)/libft.a

# TODO: Just for testing !!!
TEST =			$(TEST_DIR)/expand.c $(TEST_DIR)/arr_utils.c $(TEST_DIR)/builtins.c \
				$(TEST_DIR)/execution.c $(TEST_DIR)/setup.c $(TEST_DIR)/signals.c
LEXER =			${LEXER_DIR}/lexer.c ${LEXER_DIR}/lexer_command.c ${LEXER_DIR}/lexer_command2.c
PARSING =		${PARSING_DIR}/parser.c ${PARSING_DIR}/parser2.c ${PARSING_DIR}/tree_array.c ${PARSING_DIR}/parsing_command.c \
				${PARSING_DIR}/parsing_command2.c ${PARSING_DIR}/parsing_command3.c
BUILTINS =		$(BUILT_DIR)/builtins.c $(BUILT_DIR)/env.c $(BUILT_DIR)/export.c $(BUILT_DIR)/unset.c $(BUILT_DIR)/pwd.c \
				$(BUILT_DIR)/echo.c $(BUILT_DIR)/exit.c $(BUILT_DIR)/cd.c
EXPAND =		$(EXPAND_DIR)/expand.c $(EXPAND_DIR)/utils.c $(EXPAND_DIR)/utils/expand_modes.c \
				$(EXPAND_DIR)/utils/extract_value.c $(EXPAND_DIR)/utils/expand_heredoc.c
EXEC =			$(BUILTINS) $(EXPAND) $(EXEC_DIR)/executor.c $(EXEC_DIR)/exec_cmd.c $(EXEC_DIR)/exec_pipeline.c $(EXEC_DIR)/exec_redirection.c \
				$(EXEC_DIR)/exec_subshell.c $(EXEC_DIR)/exec_and_or.c $(EXECU_DIR)/heredoc_utils.c $(EXECU_DIR)/path_utils.c $(EXECU_DIR)/redir_utils.c \
				$(EXECU_DIR)/pipeline_utils.c
AST =			$(AST_DIR)/ast.c $(AST_DIR)/ast_examples.c
SIG =			$(SIG_DIR)/signals.c
SETUP =			$(ENV_DIR)/setup.c $(ENV_DIR)/utils.c $(ENV_DIR)/builtins_helpers.c
UTILS =			$(UTILS_DIR)/errors.c $(UTILS_DIR)/lancher.c
CLEANUP =		$(CLEANUP_DIR)/parsing.c $(CLEANUP_DIR)/execution.c
# TODO: Just for debug !!!
DEBUG =			$(DEBUG_DIR)/parsing.c $(DEBUG_DIR)/execution.c
SRCS =			minishell.c $(TEST) ${LEXER} ${PARSING} $(SETUP) $(SIG) $(AST) $(EXEC) $(UTILS) $(CLEANUP) $(DEBUG)
				
OBJS =			$(SRCS:.c=.o)

all:			$(LIBFT) $(NAME)

$(NAME):		$(OBJS)
					$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -o minishell $(LDFLAGS)

%.o: %.c		${INC_DIR}/typedef.h ${INC_DIR}/minishell.h ${INC_DIR}/parsing.h ${INC_DIR}/env.h ${INC_DIR}/signals.h ${INC_DIR}/expand.h ${INC_DIR}/builtins.h \
				${INC_DIR}/execution.h ${INC_DIR}/redirections.h ${INC_DIR}/utils.h ${INC_DIR}/cleanup.h ${INC_DIR}/debug.h
					$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
				make -C $(LIBFT_DIR)

clean:
				make clean -C $(LIBFT_DIR)
				rm -f $(OBJS)

fclean:			clean
					make fclean -C $(LIBFT_DIR)
					rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
