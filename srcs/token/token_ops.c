/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:15:22 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/03/24 18:11:30 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* External functions from token_ops_utils.c */
bool	ft_less(t_minishell *minishell, int *i);
bool	ft_lless(t_minishell *minishell, int *i);
bool	ft_ggreat(t_minishell *minishell, int *i);

bool	ft_word(t_minishell *minishell, char *input, int *i)
{
	bool	result;

	result = ft_create_word_token(minishell, input + *i);
	*i += ft_wordlen(input + *i);
	return (result);
}

bool	ft_great(t_minishell *minishell, int *i)
{
	if (!ft_create_output_token(minishell))
		return (false);
	*i += 1;
	return (true);
}

bool	ft_pipe(t_minishell *minishell, int *i)
{
	if (!ft_create_pipe_token(minishell))
		return (false);
	(*i)++;
	return (true);
}
