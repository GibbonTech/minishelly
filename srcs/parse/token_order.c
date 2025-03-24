/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:29:14 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 22:55:00 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_token_order(t_minishell *minishell)
{
	if (!ft_check_pipe(minishell))
		return (false);
	if (!ft_check_redir(minishell))
		return (false);
	return (true);
}
