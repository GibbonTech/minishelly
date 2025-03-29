/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:22:23 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 14:22:24 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_less(t_minishell *minishell, int *i)
{
	if (!ft_create_input_token(minishell))
		return (false);
	*i += 1;
	return (true);
}

bool	ft_lless(t_minishell *minishell, int *i)
{
	if (!ft_create_hdoc_token(minishell))
		return (false);
	*i += 2;
	return (true);
}

bool	ft_ggreat(t_minishell *minishell, int *i)
{
	if (!ft_create_append_token(minishell))
		return (false);
	*i += 2;
	return (true);
}
