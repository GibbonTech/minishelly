/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:00:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 16:35:56 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setup_child_exec(t_command *cmd, char *cmd_path,
		t_minishell *minishell)
{
	if (ft_apply_redirections(cmd, minishell) == -1)
	{
		free(cmd_path);
		exit(1);
	}
	ft_redirect_io(cmd);
}

void	ft_handle_exec_error(t_command *cmd, char *cmd_path, char **env_array)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->cmd_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	free(cmd_path);
	ft_free_env_array(env_array, -1);
	exit(127);
}

void	ft_child_process_setup(t_command *cmd, char *cmd_path,
		t_minishell *minishell)
{
	char	**env_array;

	ft_setup_child_exec(cmd, cmd_path, minishell);
	env_array = ft_env_to_array(minishell);
	if (!env_array)
	{
		free(cmd_path);
		exit(1);
	}
	ft_setup_child_signals();
	if (execve(cmd_path, cmd->cmd_args, env_array) == -1)
	{
		ft_handle_exec_error(cmd, cmd_path, env_array);
	}
	ft_free_env_array(env_array, -1);
	free(cmd_path);
	exit(1);
}

char	*ft_safe_find_command(char *cmd_name, t_minishell *minishell)
{
	char	*cmd_path;

	cmd_path = ft_find_command(cmd_name, minishell);
	if (!cmd_path)
		ft_handle_command_not_found(cmd_name);
	return (cmd_path);
}

int	ft_wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		return (128 + WTERMSIG(status));
	}
	return (status);
}
