/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:46:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 16:54:39 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_prepare_pipe_io(int pipe_fd[2], int prev_pipe_fd, int i,
		int cmd_count)
{
	if (prev_pipe_fd != -1)
	{
		dup2(prev_pipe_fd, STDIN_FILENO);
		close(prev_pipe_fd);
	}
	if (i < cmd_count - 1)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

static char	**ft_create_unquoted_args(t_command *cmd)
{
	char	**unquoted_args;
	int		i;

	i = 0;
	while (cmd->cmd_args[i])
		i++;
	unquoted_args = malloc(sizeof(char *) * (i + 1));
	if (!unquoted_args)
		return (NULL);
	i = 0;
	while (cmd->cmd_args[i])
	{
		unquoted_args[i] = ft_remove_quotes_from_str(cmd->cmd_args[i]);
		if (!unquoted_args[i])
			unquoted_args[i] = ft_strdup(cmd->cmd_args[i]);
		i++;
	}
	unquoted_args[i] = NULL;
	return (unquoted_args);
}

static void	ft_handle_exec_error_child(t_command *cmd, char *cmd_path,
		char **env_array, char **unquoted_args)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->cmd_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	ft_free_table(unquoted_args);
	ft_free_env_array(env_array, -1);
	free(cmd_path);
	exit(1);
}

void	ft_execute_child_command(t_command *cmd, char *cmd_path,
		t_minishell *minishell)
{
	char	**env_array;
	char	**unquoted_args;

	env_array = ft_env_to_array(minishell);
	if (!env_array)
	{
		free(cmd_path);
		exit(1);
	}
	unquoted_args = ft_create_unquoted_args(cmd);
	if (!unquoted_args)
	{
		ft_free_env_array(env_array, -1);
		free(cmd_path);
		exit(1);
	}
	ft_setup_child_signals();
	if (execve(cmd_path, unquoted_args, env_array) == -1)
		ft_handle_exec_error_child(cmd, cmd_path, env_array, unquoted_args);
	ft_free_table(unquoted_args);
}
