/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_conversion4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:01:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 16:55:57 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_init_redir_conversion(t_minishell *minishell,
		t_redir_data *redir_data)
{
	if (!ft_create_command_structures(minishell))
		return (false);
	if (!ft_init_redirection_arrays(&redir_data->redir_tokens,
			&redir_data->target_tokens))
		return (false);
	redir_data->tokens[0] = redir_data->redir_tokens;
	redir_data->tokens[1] = redir_data->target_tokens;
	redir_data->redir_count = ft_collect_redirection_tokens(minishell,
			redir_data->redir_tokens, redir_data->target_tokens);
	if (!ft_process_redirection_tokens(minishell, redir_data->tokens))
		return (false);
	return (true);
}

bool	ft_process_commands_arguments(t_minishell *minishell,
		t_redir_data *redir_data)
{
	t_command	*cmd;

	cmd = minishell->commands;
	while (cmd)
	{
		if (!ft_create_non_redir_args(cmd, redir_data->redir_tokens,
				redir_data->target_tokens, redir_data->redir_count))
		{
			free(redir_data->redir_tokens);
			free(redir_data->target_tokens);
			return (false);
		}
		cmd = cmd->next;
	}
	return (true);
}

void	ft_cleanup_redir_conversion(t_redir_data *redir_data)
{
	free(redir_data->redir_tokens);
	free(redir_data->target_tokens);
}
