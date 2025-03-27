NAME		=	minishell

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

# Colors
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
CYAN		=	\033[1;36m
PURPLE		=	\033[1;35m
RESET		=	\033[0m

# Counter for progress bar
COUNT		=	0
TOTAL		=	$(words $(SRCS_NAMES))
PERCENT		=	0

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
				exec/pipeline_utils/redir_conversion7.c \
				exec/pipeline_utils/redir_conversion8.c \
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
				parse/quotes/quotes_process.c \
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
				utils/cmd_processing_utils4.c \
				utils/error_utils.c \
				utils/ft_replace_substr.c \
				utils/ft_replace_substr_utils.c \
				utils/main_utils.c \
				utils/main_utils2.c \
				utils/input_preprocessing.c \
				utils/input_preprocessing_utils.c \
				utils/string_utils.c

OBJS_NAMES	=	$(SRCS_NAMES:.c=.o)
SRCS		=	$(addprefix $(SRCS_DIR)/,$(SRCS_NAMES))
OBJS		=	$(addprefix $(OBJ_DIR)/,$(OBJS_NAMES))

HEADER		=	-Iincludes -Ilibft

LIBFT		=	libft/libft.a

define MINISHELL_ART
$(CYAN)
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
$(RESET)
endef
export MINISHELL_ART

all: banner $(LIBFT) $(NAME)

banner:
	@clear
	@echo "$$MINISHELL_ART"
	@echo "$(PURPLE)Building your shell...$(RESET)\n"

$(NAME): $(OBJS)
	@echo "\n$(GREEN)⚡ Linking minishell...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(HEADER) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)✨ Build successful!$(RESET)\n"

$(LIBFT):
	@echo "$(YELLOW)📚 Building libft...$(RESET)"
	@make -sC libft

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)⚙️  [%3d%%] Compiling: %-50s$(RESET)\r" $$(( $(COUNT) * 100 / $(TOTAL) )) $(notdir $<)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)
	@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))

clean:
	@make -sC libft clean
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)🧹 Object files cleaned$(RESET)"

fclean: clean
	@make -sC libft fclean
	@rm -f $(NAME)
	@echo "$(GREEN)🗑️  Executable removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re banner
