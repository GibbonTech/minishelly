/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:22:27 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 14:25:31 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
