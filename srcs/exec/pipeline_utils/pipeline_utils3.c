/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:10:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 17:10:00 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_pipeline_execution(t_minishell *minishell, t_pipeline_data *data)
{
	data->prev_pipe_fd = -1;
	data->cmd_count = ft_count_commands(minishell->commands);
	if (data->cmd_count == 1)
		return (1);
	data->pids = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->pids)
		return (-1);
	data->i = 0;
	while (data->i < data->cmd_count)
	{
		data->pids[data->i] = -1;
		data->i++;
	}
	data->current = minishell->commands;
	data->i = 0;
	return (0);
}

int	ft_process_pipeline_command(t_pipeline_data *data, t_minishell *minishell)
{
	t_child_data	child_data;

	if (ft_setup_pipes(data->pipe_fd, &data->prev_pipe_fd, data->i,
			data->cmd_count) == -1)
		return (1);
	child_data.cmd = data->current;
	child_data.pipe_fd[0] = data->pipe_fd[0];
	child_data.pipe_fd[1] = data->pipe_fd[1];
	child_data.prev_pipe_fd = data->prev_pipe_fd;
	child_data.i = data->i;
	child_data.cmd_count = data->cmd_count;
	child_data.minishell = minishell;
	data->pids[data->i] = ft_execute_pipeline_cmd(data->current, &child_data);
	if (data->prev_pipe_fd != -1)
		close(data->prev_pipe_fd);
	if (data->i < data->cmd_count - 1)
	{
		close(data->pipe_fd[1]);
		data->prev_pipe_fd = data->pipe_fd[0];
	}
	return (0);
}

int	ft_finish_pipeline_execution(t_pipeline_data *data)
{
	int	status;

	status = ft_wait_for_processes(data->pids, data->cmd_count);
	free(data->pids);
	return (status);
}
