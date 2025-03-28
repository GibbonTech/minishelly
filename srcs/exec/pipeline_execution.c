/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:09:26 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/29 00:01:03 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Process all heredocs in a pipeline before executing commands
 * This ensures heredocs are handled even for invalid commands
 */
static int	ft_process_all_heredocs(t_minishell *minishell)
{
	t_command	*current;

	current = minishell->commands;
	while (current)
	{
		if (ft_has_heredoc(current))
		{
			if (ft_process_heredoc_redirections(current, minishell) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

static int	ft_handle_pipeline_init(t_minishell *minishell,
		t_pipeline_data *data)
{
	if (ft_process_all_heredocs(minishell) == -1)
		return (-1);
	if (ft_init_pipeline_execution(minishell, data) == 1)
		return (1);
	return (0);
}

static int	ft_process_pipeline(t_pipeline_data *data, t_minishell *minishell)
{
	while (data->current && data->i < data->cmd_count)
	{
		if (ft_process_pipeline_command(data, minishell))
		{
			free(data->pids);
			return (1);
		}
		data->current = data->current->next;
		data->i++;
	}
	return (0);
}

int	ft_execute_pipeline_with_redir(t_minishell *minishell)
{
	t_pipeline_data	data;
	int				init_status;
	int				status;

	init_status = ft_handle_pipeline_init(minishell, &data);
	if (init_status == -1)
		return (1);
	if (init_status == 1)
		return (ft_execute_command_with_redir(minishell, minishell->commands));
	if (ft_process_pipeline(&data, minishell))
		return (1);
	status = ft_finish_pipeline_execution(&data);
	return (status);
}

bool	ft_convert_to_commands_with_redir(t_minishell *minishell)
{
	t_redir_data	redir_data;
	bool			result;

	if (!ft_init_redir_conversion(minishell, &redir_data))
		return (false);
	result = ft_process_commands_arguments(minishell, &redir_data);
	ft_cleanup_redir_conversion(&redir_data);
	return (result);
}
