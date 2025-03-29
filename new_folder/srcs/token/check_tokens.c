/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:22:06 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 14:22:07 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_error(char *error_message)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("'\n", 2);
	return ;
}

bool	ft_check_pipe(t_minishell *minishell)
{
	t_token	*current;

	current = minishell->token_list;
	while (current)
	{
		if (current->token_type == TOKEN_PIPE)
		{
			if (current->token_id == 0 && !current->next_token)
				return (ft_token_error(current->token_name), false);
			else if (current->token_id == 0 || !current->next_token)
				return (ft_token_error(current->token_name), false);
			else if (current->next_token->token_type == TOKEN_PIPE)
				return (ft_token_error(current->token_name), false);
			else if (current->next_token->token_redir != REDIR_NONE)
				return (ft_token_error(current->token_name), false);
		}
		current = current->next_token;
	}
	return (true);
}

bool	ft_check_redir(t_minishell *minishell)
{
	t_token	*current;

	current = minishell->token_list;
	while (current)
	{
		if (current->token_redir != REDIR_NONE)
		{
			if (!current->next_token)
				return (ft_token_error("newline"), false);
			else if (current->next_token->token_type == TOKEN_PIPE)
				return (ft_token_error("|"), false);
			else if (current->next_token->token_redir != REDIR_NONE)
				return (ft_token_error(current->token_name), false);
			else if (current->token_id == ft_last_token_id(minishell) - 1
				&& current->next_token->token_redir != REDIR_NONE)
				return (ft_token_error(current->next_token->token_name), false);
		}
		current = current->next_token;
	}
	return (true);
}
