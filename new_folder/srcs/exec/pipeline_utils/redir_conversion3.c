/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_conversion3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:49:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 16:55:36 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_redirection_arg(char *arg, t_token **redir_tokens,
		t_token **target_tokens, int redir_count)
{
	int	j;

	j = 0;
	while (j < redir_count)
	{
		if (ft_strncmp(arg, redir_tokens[j]->token_name,
				ft_strlen(redir_tokens[j]->token_name) + 1) == 0
			|| ft_strncmp(arg, target_tokens[j]->token_name,
				ft_strlen(target_tokens[j]->token_name) + 1) == 0)
		{
			return (true);
		}
		j++;
	}
	return (false);
}

int	ft_count_non_redir_args(char **cmd_args, t_token **redir_tokens,
		t_token **target_tokens, int redir_count)
{
	int	i;
	int	arg_count;

	i = 0;
	arg_count = 0;
	while (cmd_args[i])
	{
		if (!ft_is_redirection_arg(cmd_args[i], redir_tokens, target_tokens,
				redir_count))
			arg_count++;
		i++;
	}
	return (arg_count);
}

bool	ft_free_partial_args(char **args, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(args[i]);
		i++;
	}
	free(args);
	return (false);
}

void	ft_free_cmd_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
