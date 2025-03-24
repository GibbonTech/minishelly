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

void	ft_execute_child_command(t_command *cmd, char *cmd_path,
		t_minishell *minishell)
{
	ft_redirect_io(cmd);
	if (execve(cmd_path, cmd->cmd_args, ft_env_to_array(minishell)) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(cmd_path);
		exit(1);
	}
}
