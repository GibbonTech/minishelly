/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:03:52 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/29 00:04:24 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Token operations from token_ops.c and token_ops_utils.c */
static bool	ft_process_pipe_token(t_minishell *minishell, int *i)
{
	return (ft_pipe(minishell, i));
}

static bool	ft_process_operator(t_minishell *minishell, char *input, int *i)
{
	if (input[*i] == '|')
		return (ft_process_pipe_token(minishell, i));
	else
		return (ft_process_redir(minishell, input, i));
}

bool	ft_tokenization(t_minishell *minishell, char *input, int i)
{
	while (input[i])
	{
		if (ft_space(input[i]))
		{
			i++;
			continue ;
		}
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			if (!ft_process_operator(minishell, input, &i))
				return (false);
		}
		else
		{
			if (!ft_word(minishell, input, &i))
				return (false);
		}
	}
	return (true);
}

bool	ft_parsing(t_minishell *minishell, char *input)
{
	if (ft_only_spaces(input))
		return (false);
	if (ft_not_handling(input))
	{
		minishell->exit_status = 2;
		return (false);
	}
	if (minishell->token_list)
		ft_free_token_list(minishell);
	if (!ft_tokenization(minishell, input, 0))
	{
		ft_error("tokenization error");
		minishell->exit_status = 2;
		return (false);
	}
	if (!ft_token_order(minishell))
	{
		ft_error("syntax error: invalid token order");
		minishell->exit_status = 2;
		return (false);
	}
	return (true);
}
