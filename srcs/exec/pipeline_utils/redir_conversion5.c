/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_conversion5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:20:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 19:40:39 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_process_redir_token(t_command *cmd, t_token *current,
		t_token **tokens[2])
{
	t_token	*next_token;

	next_token = current->next_token;
	if (!next_token || next_token->token_type != TOKEN_WORD)
		return (ft_free_tokens_and_fail(tokens[0], tokens[1]));
	return (ft_add_redirection_by_type(cmd, current, next_token, tokens));
}

bool	ft_process_token_list(t_minishell *minishell, t_token **tokens[2],
		t_token *current, int *cmd_idx)
{
	t_command	*cmd;

	if (current->token_type == TOKEN_PIPE)
	{
		(*cmd_idx)++;
		return (true);
	}
	if (current->token_redir != REDIR_NONE)
	{
		cmd = ft_get_command_at_index(minishell, *cmd_idx);
		if (!cmd)
			return (ft_free_tokens_and_fail(tokens[0], tokens[1]));
		if (!ft_process_redir_token(cmd, current, tokens))
			return (false);
	}
	return (true);
}

bool	ft_process_redirection_tokens(t_minishell *minishell,
		t_token **tokens[2])
{
	t_token	*current;
	int		cmd_idx;

	cmd_idx = 0;
	current = minishell->token_list;
	while (current)
	{
		if (!ft_process_token_list(minishell, tokens, current, &cmd_idx))
			return (false);
		current = current->next_token;
	}
	return (true);
}
