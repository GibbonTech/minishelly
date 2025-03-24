/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:15:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 19:40:11 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execute_in_child(t_child_data *data, char *cmd_path)
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

static pid_t	ft_handle_child_process(t_child_data *data)
{
	char	*cmd_path;
	pid_t	pid;

	cmd_path = ft_safe_find_command(data->cmd->cmd_name, data->minishell);
	if (!cmd_path)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		return (-1);
	}
	if (pid == 0)
		ft_execute_in_child(data, cmd_path);
	free(cmd_path);
	return (pid);
}

pid_t	ft_execute_pipeline_cmd(t_command *cmd, t_child_data *data)
{
	data->cmd = cmd;
	if (data->cmd_count == 1 && ft_is_builtin(cmd->cmd_name))
		return (-1);
	return (ft_handle_child_process(data));
}
