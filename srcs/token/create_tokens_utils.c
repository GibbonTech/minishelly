/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:25:15 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/03/24 18:00:30 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_create_append_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->token_name = ft_strdup(">>");
	if (!new_token->token_name)
		return (free(new_token), false);
	new_token->token_type = TOKEN_DGREAT;
	new_token->token_redir = REDIR_APPEND;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}

bool	ft_create_hdoc_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->token_name = ft_strdup("<<");
	if (!new_token->token_name)
		return (free(new_token), false);
	new_token->token_type = TOKEN_DLESS;
	new_token->token_redir = REDIR_HEREDOC;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}

bool	ft_create_word_token(t_minishell *minishell, char *input)
{
	t_token	*new_token;
	int		len;

	len = ft_wordlen(input);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->token_id = ft_last_token_id(minishell) + 1;
	new_token->token_name = ft_substr(input, 0, len);
	if (!new_token->token_name)
	{
		free(new_token);
		return (false);
	}
	new_token->token_type = TOKEN_WORD;
	new_token->token_redir = REDIR_NONE;
	new_token->quote_type = QUOTE_NONE;
	new_token->next_token = NULL;
	ft_set_quote_type(new_token);
	ft_append_token(minishell, new_token);
	return (true);
}
