/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:36:35 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 00:06:12 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_process_double_redir(t_minishell *minishell, char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
		return (ft_ggreat(minishell, i));
	else if (input[*i] == '<' && input[*i + 1] == '<')
		return (ft_lless(minishell, i));
	return (true);
}

static bool	ft_process_single_redir(t_minishell *minishell, char *input, int *i)
{
	if (input[*i] == '>')
		return (ft_great(minishell, i));
	else if (input[*i] == '<')
		return (ft_less(minishell, i));
	return (true);
}

bool	ft_process_redir(t_minishell *minishell, char *input, int *i)
{
	if (!ft_process_double_redir(minishell, input, i))
		return (false);
	if (!ft_process_single_redir(minishell, input, i))
		return (false);
	return (true);
}
