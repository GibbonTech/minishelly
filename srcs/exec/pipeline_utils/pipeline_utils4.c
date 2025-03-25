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

/* Declarations for functions now in pipeline_utils5.c */
void	ft_execute_in_child(t_child_data *data, char *cmd_path);
void	ft_execute_builtin_in_child(t_child_data *data);
pid_t	ft_handle_builtin_in_pipeline(t_child_data *data);

static pid_t	ft_handle_external_command(t_child_data *data, char *cmd_path)
{
	pid_t	pid;

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

static pid_t	ft_handle_child_process(t_child_data *data)
{
	char	*cmd_path;

	if (ft_is_builtin(data->cmd->cmd_name))
		return (ft_handle_builtin_in_pipeline(data));
	cmd_path = ft_find_command(data->cmd->cmd_name, data->minishell);
	if (!cmd_path)
	{
		ft_handle_command_not_found(data->cmd->cmd_name);
		return (-2);
	}
	return (ft_handle_external_command(data, cmd_path));
}

pid_t	ft_execute_pipeline_cmd(t_command *cmd, t_child_data *data)
{
	data->cmd = cmd;
	if (!cmd->cmd_name || !*cmd->cmd_name)
		return (-2);
	if (data->cmd_count == 1 && ft_is_builtin(cmd->cmd_name))
		return (-1);
	return (ft_handle_child_process(data));
}
