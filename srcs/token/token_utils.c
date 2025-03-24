/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:53:48 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/24 17:51:18 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token_list(t_minishell *minishell)
{
	t_token	*current_token;
	t_token	*next_token;

	if (!minishell)
		return ;
	current_token = minishell->token_list;
	while (current_token)
	{
		next_token = current_token->next_token;
		if (current_token->token_name)
			free(current_token->token_name);
		free(current_token);
		current_token = next_token;
	}
	minishell->token_list = NULL;
}

void	ft_append_token(t_minishell *minishell, t_token *new_token)
{
	t_token	*current_token;

	if (minishell->token_list == NULL)
	{
		new_token->token_id = 0;
		minishell->token_list = new_token;
	}
	else
	{
		current_token = minishell->token_list;
		while (current_token->next_token != NULL)
			current_token = current_token->next_token;
		new_token->token_id = current_token->token_id + 1;
		current_token->next_token = new_token;
	}
	return ;
}

int	ft_last_token_id(t_minishell *minishell)
{
	t_token	*current_token;

	if (!minishell->token_list)
		return (-1);
	current_token = minishell->token_list;
	while (current_token->next_token)
		current_token = current_token->next_token;
	return (current_token->token_id);
}
