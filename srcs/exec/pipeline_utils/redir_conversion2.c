/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_conversion2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:48:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 19:40:31 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_get_command_at_index(t_minishell *minishell, int cmd_idx)
{
	t_command	*cmd;
	int			i;

	cmd = minishell->commands;
	i = 0;
	while (cmd && i < cmd_idx)
	{
		cmd = cmd->next;
		i++;
	}
	return (cmd);
}

bool	ft_add_redirection_by_type(t_command *cmd, t_token *token,
		t_token *target, t_token **tokens[2])
{
	if (token->token_type == TOKEN_LESS)
	{
		if (!ft_add_redirection(cmd, REDIR_INPUT, target->token_name))
			return (ft_free_tokens_and_fail(tokens[0], tokens[1]));
	}
	else if (token->token_type == TOKEN_GREAT)
	{
		if (!ft_add_redirection(cmd, REDIR_OUTPUT, target->token_name))
			return (ft_free_tokens_and_fail(tokens[0], tokens[1]));
	}
	else if (token->token_type == TOKEN_DGREAT)
	{
		if (!ft_add_redirection(cmd, REDIR_APPEND, target->token_name))
			return (ft_free_tokens_and_fail(tokens[0], tokens[1]));
	}
	else if (token->token_type == TOKEN_DLESS)
	{
		if (!ft_add_redirection(cmd, REDIR_HEREDOC, target->token_name))
			return (ft_free_tokens_and_fail(tokens[0], tokens[1]));
	}
	return (true);
}

bool	ft_free_tokens_and_fail(t_token **redir_tokens, t_token **target_tokens)
{
	free(redir_tokens);
	free(target_tokens);
	return (false);
}
