/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:29:21 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 22:55:13 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Get the quote type for a character
 * @param c Character to check
 * @return QUOTE_SINGLE for single quotes, QUOTE_DOUBLE for double quotes,
 *         QUOTE_NONE otherwise
 */
static t_quote_type	get_quote_type(char c)
{
	if (c == '\'')
		return (QUOTE_SINGLE);
	if (c == '\"')
		return (QUOTE_DOUBLE);
	return (QUOTE_NONE);
}

void	ft_set_quote_type(t_token *token)
{
	int				i;
	t_quote_type	current_quote;

	if (!token || !token->token_name)
		return ;
	i = 0;
	current_quote = QUOTE_NONE;
	while (token->token_name[i])
	{
		if (is_quote(token->token_name[i]))
		{
			if (current_quote == QUOTE_NONE)
				current_quote = get_quote_type(token->token_name[i]);
			else if (current_quote == get_quote_type(token->token_name[i]))
				current_quote = QUOTE_NONE;
		}
		i++;
	}
	token->quote_type = current_quote;
}
