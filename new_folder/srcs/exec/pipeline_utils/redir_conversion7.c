/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_conversion7.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:32:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/27 07:32:21 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
