NAME		=	minishell

CC			=	cc
C_FLAGS		=	-Wall -Wextra -Werror -g3 -MMD -MP

SRCS_DIR	=	srcs
OBJ_DIR		=	objs
SRCS_NAMES	=	main.c \
				builtins/cd.c \
				builtins/cd_utils.c \
				builtins/echo.c \
				builtins/env.c \
				builtins/exit.c \
				builtins/exit_numeric.c \
				builtins/export.c \
				builtins/export_utils.c \
				builtins/pwd.c \
				builtins/unset.c \
				command/command_utils1.c \
				command/command_utils2.c \
				command/command_utils3.c \
				command/command_utils4.c \
				exec/builtin_execution.c \
				exec/cmd_list.c \
				exec/cmd_list_utils.c \
				exec/cmd_list_utils2.c \
				exec/cmd_list_utils3.c \
				exec/cmd_list_utils4.c \
				exec/cmd_list_utils5.c \
				exec/cmd_list_utils6.c \
				exec/cmd_list_utils7.c \
				exec/cmd_list_utils8.c \
				exec/cmd_list_utils9.c \
				exec/command_execution.c \
				exec/command_execution_utils.c \
				exec/command_execution_utils2.c \
				exec/env_utils.c \
				exec/path_utils.c \
				exec/pipeline_execution.c \
				exec/pipeline_utils/pipeline_utils1.c \
				exec/pipeline_utils/pipeline_utils2.c \
				exec/pipeline_utils/pipeline_utils3.c \
				exec/pipeline_utils/pipeline_utils4.c \
				exec/pipeline_utils/pipeline_utils5.c \
				exec/pipeline_utils/redir_conversion1.c \
				exec/pipeline_utils/redir_conversion2.c \
				exec/pipeline_utils/redir_conversion3.c \
				exec/pipeline_utils/redir_conversion4.c \
				exec/pipeline_utils/redir_conversion5.c \
				exec/pipeline_utils/redir_conversion6.c \
				expand/envar.c \
				expand/envar_utils.c \
				expand/var_utils.c \
				parse/char_utils.c \
				parse/ft_split_quotes.c \
				parse/ft_split_quotes_utils.c \
				parse/ft_split_quotes_utils2.c \
				parse/parse_char.c \
				parse/parsing.c \
				parse/quotes.c \
				parse/quotes/quotes_utils.c \
				parse/token_order.c \
				redirection/heredoc.c \
				redirection/heredoc_util1.c \
				redirection/heredoc_util2.c \
				redirection/heredoc_util3.c \
				redirection/redirection1.c \
				redirection/redirection2.c \
				signals/signal_handlers.c \
				signals/signal_setup.c \
				token/check_tokens.c \
				token/create_tokens.c \
				token/create_tokens_utils.c \
				token/token_ops.c \
				token/token_ops_utils.c \
				token/token_utils.c \
				utils/cmd_processing.c \
				utils/cmd_processing_utils2.c \
				utils/cmd_processing_utils3.c \
				utils/error_utils.c \
				utils/ft_replace_substr.c \
				utils/ft_replace_substr_utils.c \
				utils/main_utils.c \
				utils/main_utils2.c \
				utils/input_preprocessing.c \
				utils/input_preprocessing_utils.c

OBJS_NAMES	=	$(SRCS_NAMES:.c=.o)
SRCS		=	$(addprefix $(SRCS_DIR)/,$(SRCS_NAMES))
OBJS		=	$(addprefix $(OBJ_DIR)/,$(OBJS_NAMES))
DEPS		=	$(OBJS:.o=.d)

HEADER		=	-Iincludes -Ilibft

LIBFT		=	libft/libft.a

# Colors for minimal output
GREEN		=	\033[1;32m
RED			=	\033[1;31m
RESET		=	\033[0m

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking minishell...$(RESET)"
	@$(CC) $(C_FLAGS) $(OBJS) $(HEADER) $(LIBFT) -lreadline -o $(NAME) || (echo "$(RED)Error: Linking failed!$(RESET)" && exit 1)
	@echo "$(GREEN)Build successful!$(RESET)"

$(LIBFT):
	@make -sC libft

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@printf "$(GREEN)•$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@ $(HEADER) || (printf "\n$(RED)Error: Compilation of $< failed!$(RESET)\n" && exit 1)

clean:
	@make -sC libft clean
	@rm -rf $(OBJ_DIR)
	@find . -name "*.o" -type f -not -path "./libft/*" -delete
	@echo "$(GREEN)Object files cleaned$(RESET)"

fclean: clean
	@make -sC libft fclean
	@rm -rf $(NAME)
	@find . -name "*.o" -type f -delete
	@echo "$(GREEN)Executable removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
