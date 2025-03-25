/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:30:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/25 16:23:25 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_in_child(t_child_data *data, char *cmd_path)
{
	ft_prepare_pipe_io(data->pipe_fd, data->prev_pipe_fd, data->i,
		data->cmd_count);
	if (ft_apply_redirections(data->cmd, data->minishell) == -1)
	{
		free(cmd_path);
		exit(1);
	}
	ft_execute_child_command(data->cmd, cmd_path, data->minishell);
}

void	ft_execute_builtin_in_child(t_child_data *data)
{
	int	status;

	ft_prepare_pipe_io(data->pipe_fd, data->prev_pipe_fd, data->i,
		data->cmd_count);
	if (ft_apply_redirections(data->cmd, data->minishell) == -1)
		exit(1);
	ft_redirect_io(data->cmd);
	status = ft_execute_specific_builtin(data->minishell, data->cmd);
	exit(status);
}

pid_t	ft_handle_builtin_in_pipeline(t_child_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_execute_builtin_in_child(data);
	return (pid);
}
