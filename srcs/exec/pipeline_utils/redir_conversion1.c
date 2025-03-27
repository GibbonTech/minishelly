/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_conversion1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:47:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/27 07:32:21 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_init_redirection_arrays(t_token ***redir_tokens,
		t_token ***target_tokens)
{
	*redir_tokens = malloc(sizeof(t_token *) * 100);
	*target_tokens = malloc(sizeof(t_token *) * 100);
	if (!*redir_tokens || !*target_tokens)
	{
		if (*redir_tokens)
			free(*redir_tokens);
		if (*target_tokens)
			free(*target_tokens);
		return (false);
	}
	return (true);
}

bool	ft_create_command_structures(t_minishell *minishell)
{
	t_cmd		*current_cmd;
	t_command	*new_cmd;
	bool		has_commands;

	if (minishell->commands)
		ft_free_command_list(minishell);
	current_cmd = minishell->cmd_list;
	has_commands = false;
	while (current_cmd)
	{
		new_cmd = ft_create_command_struct(current_cmd->cmd_name,
				current_cmd->cmd_args);
		if (!new_cmd)
			return (false);
		if (!ft_add_command(minishell, new_cmd))
		{
			ft_delete_command(new_cmd);
			return (false);
		}
		has_commands = true;
		current_cmd = current_cmd->next_cmd;
	}
	if (!has_commands)
		return (ft_handle_empty_command_list(minishell));
	return (true);
}
