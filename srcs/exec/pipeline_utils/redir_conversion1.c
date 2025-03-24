/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_conversion1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:47:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 19:40:21 by ykhomsi          ###   ########.fr       */
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

	if (minishell->commands)
		ft_free_command_list(minishell);
	current_cmd = minishell->cmd_list;
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
		current_cmd = current_cmd->next_cmd;
	}
	return (true);
}

int	ft_collect_redirection_tokens(t_minishell *minishell,
		t_token **redir_tokens, t_token **target_tokens)
{
	t_token	*current_token;
	t_token	*next_token;
	int		redir_count;

	redir_count = 0;
	current_token = minishell->token_list;
	while (current_token)
	{
		if (current_token->token_redir != REDIR_NONE)
		{
			next_token = current_token->next_token;
			if (next_token && next_token->token_type == TOKEN_WORD)
			{
				redir_tokens[redir_count] = current_token;
				target_tokens[redir_count] = next_token;
				redir_count++;
			}
		}
		current_token = current_token->next_token;
	}
	return (redir_count);
}
