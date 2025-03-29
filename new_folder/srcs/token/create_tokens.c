/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:22:19 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 14:22:19 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* External functions from create_tokens_utils.c */
bool	ft_create_append_token(t_minishell *minishell);
bool	ft_create_hdoc_token(t_minishell *minishell);
bool	ft_create_word_token(t_minishell *minishell, char *input);

bool	ft_create_pipe_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->token_name = ft_strdup("|");
	if (!new_token->token_name)
		return (free(new_token), false);
	new_token->token_type = TOKEN_PIPE;
	new_token->token_redir = REDIR_NONE;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}

bool	ft_create_output_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->token_name = ft_strdup(">");
	if (!new_token->token_name)
		return (free(new_token), false);
	new_token->token_type = TOKEN_GREAT;
	new_token->token_redir = REDIR_OUTPUT;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}

bool	ft_create_input_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->token_name = ft_strdup("<");
	if (!new_token->token_name)
		return (free(new_token), false);
	new_token->token_type = TOKEN_LESS;
	new_token->token_redir = REDIR_INPUT;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}
