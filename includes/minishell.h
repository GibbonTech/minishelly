/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:09:30 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/25 12:20:15 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

/* Global variable for signal handling */
extern volatile sig_atomic_t	g_exit_codes;

/* ENUMERATIONS */
typedef enum e_redir_type
{
	REDIR_NONE,
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_GREAT,
	TOKEN_LESS,
	TOKEN_DGREAT,
	TOKEN_DLESS
}	t_token_type;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_type;

/* STRUCTURES */
typedef struct s_exp_data
{
	int		i;
	int		j;
	char	quote_state;
}	t_exp_data;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				*cmd_name;
	char				**cmd_args;
	t_redir				*redirections;
	int					input_fd;
	int					output_fd;
	struct s_command	*next;
}	t_command;

typedef struct s_cmd
{
	char			*cmd_name;
	char			**cmd_args;
	struct s_cmd	*next_cmd;
}	t_cmd;

typedef struct s_token
{
	int				token_id;
	char			*token_name;
	t_token_type	token_type;
	t_redir_type	token_redir;
	t_quote_type	quote_type;
	struct s_token	*next_token;
}	t_token;

typedef struct s_envar
{
	char			*key;
	char			*value;
	struct s_envar	*next;
}	t_envar;

typedef struct s_minishell
{
	t_token			*token_list;
	t_envar			*env_list;
	t_cmd			*cmd_list;
	t_command		*commands;
	int				exit_status;
}	t_minishell;

typedef struct s_child_data
{
	t_command		*cmd;
	int				pipe_fd[2];
	int				prev_pipe_fd;
	int				i;
	int				cmd_count;
	t_minishell		*minishell;
}	t_child_data;

typedef struct s_pipeline_data
{
	t_command		*current;
	int				pipe_fd[2];
	int				prev_pipe_fd;
	pid_t			*pids;
	int				cmd_count;
	int				i;
}	t_pipeline_data;

typedef struct s_redir_data
{
	t_token			**redir_tokens;
	t_token			**target_tokens;
	t_token			**tokens[2];
	int				redir_count;
}	t_redir_data;

/* FUNCTION PROTOTYPES */

/* Main and initialization */
int			initialize_minishell(t_minishell **minishell, char **envp);
int			process_input(t_minishell *minishell, char *input);
void		ft_cleanup_minishell(t_minishell *minishell);
int			ft_init_minishell_struct(t_minishell **minishell);
int			ft_prepare_commands(t_minishell *minishell, char *input);
int			ft_execute_and_cleanup(t_minishell *minishell);
void		ft_cleanup_env_vars(t_minishell *minishell);
void		ft_cleanup_data_structures(t_minishell *minishell);
void		ft_reset_command_lists(t_minishell *minishell);
int			ft_check_terminal(void);
int			ft_handle_input(char **input);
int			ft_run_shell_loop(t_minishell *minishell);
char		*ft_insert_spaces_around_operators(char *input);
void		ft_handle_operator(char *input, char *result, int *i, int *j);

/* Builtins */
int			ft_cd(t_minishell *minishell, char **args);
int			ft_cd_home(t_minishell *minishell);
int			ft_cd_previous(t_minishell *minishell);
int			ft_change_dir(t_minishell *minishell, char *path);
int			ft_update_pwd(t_minishell *minishell);
int			ft_pwd(t_minishell *minishell);
int			ft_echo(char **args);
int			ft_export(t_minishell *minishell, char **args);
bool		ft_is_valid_identifier(char *arg);
char		**ft_env_to_array(t_minishell *minishell);
int			ft_unset(t_minishell *minishell, char **args);
int			ft_env(t_minishell *minishell);
int			ft_exit(t_minishell *minishell, char **args);
int			ft_is_numeric(char *str);
long		ft_atol(const char *str, int *error);
void		ft_clean_exit(t_minishell *minishell, int status);
void		ft_print_numeric_error(char *cmd, char *arg,
				char *message, int *code);
void		ft_update_env_var(t_minishell *minishell, char *key, char *value);
int			ft_print_invalid_identifier(char *arg);
void		ft_print_export_list(t_minishell *minishell);

/* Parsing */
bool		ft_parsing(t_minishell *minishell, char *input);
int			ft_wordlen(char *input);
bool		ft_notword(char c);
bool		ft_space(char c);
bool		ft_only_spaces(char *input);
bool		ft_not_handling(char *input);
bool		ft_check_pipe(t_minishell *minishell);
bool		ft_check_redir(t_minishell *minishell);
void		ft_free_split(char **split, int size);
char		**ft_split_quotes(char const *s, char c);
void		ft_skip_quoted_word(char const *s, int *i);
bool		ft_token_order(t_minishell *minishell);
bool		ft_cmd_struct(char *input, t_minishell *minishell);
bool		ft_convert_to_commands_with_redir(t_minishell *minishell);

/* Token operations */
bool		ft_pipe(t_minishell *minishell, int *i);
bool		ft_less(t_minishell *minishell, int *i);
bool		ft_great(t_minishell *minishell, int *i);
bool		ft_ggreat(t_minishell *minishell, int *i);
bool		ft_lless(t_minishell *minishell, int *i);
bool		ft_word(t_minishell *minishell, char *input, int *i);
void		ft_free_token_list(t_minishell *minishell);
int			ft_last_token_id(t_minishell *minishell);
bool		ft_create_output_token(t_minishell *minishell);
bool		ft_create_pipe_token(t_minishell *minishell);
bool		ft_create_word_token(t_minishell *minishell, char *input);
bool		ft_create_append_token(t_minishell *minishell);
bool		ft_create_input_token(t_minishell *minishell);
bool		ft_create_hdoc_token(t_minishell *minishell);
void		ft_append_token(t_minishell *minishell, t_token *token);

/* Quote handling */
int			is_quote(char c);
t_quote_type	 get_quote_type(char c);
void		ft_set_quote_type(t_token *token);
char		*ft_remove_quotes_from_str(char *str);
void		ft_remove_quotes(t_token *token);
char		*ft_process_quotes_simple(char *str, char **result);

/* Command handling */
bool		ft_create_cmd_list(t_minishell *minishell, char **cmd_cells);
bool		ft_create_cmd(t_minishell *minishell, char **cmd_args);
void		ft_free_table(char **table);
bool		ft_process_cmd_list(char *cmd_cell, t_minishell *minishell);
char		**ft_split_cmd_args(char *cmd_cell);
void		ft_free_cmd_list(t_cmd *cmd_list);
t_redir		*ft_create_redirection(t_redir_type type, char *filename);
t_command	*ft_create_command_struct(char *cmd_name, char **cmd_args);
bool		ft_init_command(t_command *cmd);
bool		ft_add_command(t_minishell *minishell, t_command *cmd);
t_command	*ft_last_command(t_minishell *minishell);
void		ft_free_redirection(t_redir *redir);
void		ft_delete_command(t_command *cmd);
void		ft_free_command_list(t_minishell *minishell);
bool		ft_add_redirection(t_command *cmd, t_redir_type type,
				char *filename);

/* String manipulation */
bool		ft_process_word(char **split, char const *s, char c, int pos[2]);
char		*ft_replace_substr(char *str, int start, int len,
				char *replacement);

/* Environment variables */
char		*ft_expand_var(t_minishell *minishell, char *var_name);
bool		ft_envar_list(char **envp, t_minishell *minishell);
bool		ft_add_envar(t_minishell *minishell, char *key, char *value);
char		*ft_get_key(char *envar, char delimiter);
char		*ft_get_value(char *envar, int start);
char		*ft_getenv(char *key, t_minishell *minishell);
char		*ft_get_var_name(char *line, int *i);
int			ft_is_var_char(char c);
void		ft_skip_normal_word(char const *s, char c, int *i);

/* Command execution */
char		*ft_find_command(char *cmd_name, t_minishell *minishell);
int			ft_is_builtin(char *cmd_name);
int			ft_execute_specific_builtin(t_minishell *minishell, t_command *cmd);
int			ft_execute_command_with_redir(t_minishell *minishell,
				t_command *cmd);
int			ft_execute_pipeline_with_redir(t_minishell *minishell);
void		ft_free_env_array(char **env_array, int count);
char		*ft_check_full_path(char *cmd_name);
char		*ft_check_dir_for_cmd(char *dir, char *cmd_name);
int			ft_handle_command_not_found(char *cmd_name);
void		ft_setup_child_exec(t_command *cmd, char *cmd_path,
				t_minishell *minishell);
void		ft_handle_exec_error(t_command *cmd, char *cmd_path,
				char **env_array);
void		ft_child_process_setup(t_command *cmd, char *cmd_path,
				t_minishell *minishell);
char		*ft_safe_find_command(char *cmd_name, t_minishell *minishell);
int			ft_wait_for_child(pid_t pid);
int			ft_execute_builtin_with_redir(t_minishell *minishell,
				t_command *cmd, int stdin_backup, int stdout_backup);
int			ft_execute_external_command(t_minishell *minishell,
				t_command *cmd, char *cmd_path);

/* Pipeline execution */
int			ft_count_commands(t_command *commands);
int			ft_setup_pipes(int pipe_fd[2], int *prev_pipe_fd,
				int i, int cmd_count);
int			ft_wait_for_processes(pid_t *pids, int cmd_count);
void		ft_prepare_pipe_io(int pipe_fd[2], int prev_pipe_fd,
				int i, int cmd_count);
void		ft_execute_child_command(t_command *cmd, char *cmd_path,
				t_minishell *minishell);
pid_t		ft_execute_pipeline_cmd(t_command *cmd, t_child_data *data);
int			ft_init_pipeline_execution(t_minishell *minishell,
				t_pipeline_data *data);
int			ft_process_pipeline_command(t_pipeline_data *data,
				t_minishell *minishell);
int			ft_finish_pipeline_execution(t_pipeline_data *data);

/* Redirection handling */
int			ft_input_redirection(char *filename, t_command *cmd);
int			ft_output_redirection(char *filename, t_command *cmd);
int			ft_append_redirection(char *filename, t_command *cmd);
void		ft_redirect_io(t_command *cmd);
void		ft_restore_io(int stdin_backup, int stdout_backup);
int			ft_apply_redirections(t_command *cmd, t_minishell *minishell);
bool		ft_init_redirection_arrays(t_token ***redir_tokens,
				t_token ***target_tokens);
bool		ft_create_command_structures(t_minishell *minishell);
int			ft_collect_redirection_tokens(t_minishell *minishell,
				t_token **redir_tokens, t_token **target_tokens);
t_command	*ft_get_command_at_index(t_minishell *minishell, int cmd_idx);
bool		ft_add_redirection_by_type(t_command *cmd, t_token *token,
				t_token *target, t_token **tokens[2]);
bool		ft_free_tokens_and_fail(t_token **redir_tokens,
				t_token **target_tokens);
bool		ft_process_redirection_tokens(t_minishell *minishell,
				t_token **tokens[2]);
bool		ft_is_redirection_arg(char *arg, t_token **redir_tokens,
				t_token **target_tokens, int redir_count);
int			ft_count_non_redir_args(char **cmd_args, t_token **redir_tokens,
				t_token **target_tokens, int redir_count);
bool		ft_create_non_redir_args(t_command *cmd, t_token **redir_tokens,
				t_token **target_tokens, int redir_count);
bool		ft_free_partial_args(char **args, int count);
void		ft_free_cmd_args(char **args);
bool		ft_init_redir_conversion(t_minishell *minishell,
				t_redir_data *redir_data);
bool		ft_process_commands_arguments(t_minishell *minishell,
				t_redir_data *redir_data);
void		ft_cleanup_redir_conversion(t_redir_data *redir_data);
int			ft_process_heredoc_redirections(t_command *cmd, t_minishell *minishell);

/* Heredoc handling */
void		ft_write_heredoc(int fd, char *line);
void		ft_process_heredoc_line(char **line, t_minishell *minishell);
void		ft_expand_env_var(char **line, t_minishell *minishell, int i);
int			ft_check_delimiter(char *line, char *delimiter);
int			ft_process_heredoc(t_command *cmd, char *delimiter,
				t_minishell *minishell);
char		*ft_get_heredoc_var_value(char *var_name, t_minishell *minishell);
int			ft_read_heredoc(int fd, char *delimiter, t_minishell *minishell);
char		*ft_create_heredoc_file(int *count);
int			ft_open_heredoc_file(char *file, int *fd);
int			ft_setup_heredoc_input(t_command *cmd, char *file);
bool		ft_has_heredoc(t_command *cmd);

/* Expansion utilities */
char		*ft_expand_env_vars(t_minishell *minishell, char *str);
bool		ft_process_expand_args(t_minishell *minishell, char **cmd_args,
				char **expanded_args);
bool		ft_process_expansion_loop(t_minishell *minishell, char *str,
				char **expanded, int *pos);
bool		ft_process_char_in_loop(t_minishell *minishell, char *str,
				char **expanded, int *pos);
bool		ft_check_buffer_size(char **expanded, int *pos, int *buffer_size);
char		*ft_expand_env_var_value(t_minishell *minishell, char *str, int *i);
char		*ft_init_expansion(char *str, int *buffer_size);
int			ft_copy_var_value(char **expanded, char *var_value, int j);
int			ft_handle_quotes(char *str, char *expanded, int *i, int *j);
int			ft_handle_dollar_sign(t_minishell *minishell, char *str,
				char **expanded, int *i);
bool		ft_check_simple_case(char *str, char **result);
bool		ft_resize_if_needed(char **expanded, int j, int *buffer_size);
bool		ft_init_cmd_creation(t_minishell *minishell, char **cmd_args,
				t_cmd **new_cmd, char ***expanded_args);

/* Signal handling */
void		handle_signal_parent(int num);
void		ft_sigint_handler(int sig);
void		ft_sigint_child_handler(int sig);
void		ft_heredoc_sigint_handler(int sig);
int			sig_event(void);
void		ft_setup_interactive_signals(void);
void		ft_setup_exec_signals(void);
void		ft_setup_heredoc_signals(void);
void		ft_setup_child_signals(void);
void		ft_reset_signals(void);

/* Error handling */
void		ft_error(char *message);

#endif