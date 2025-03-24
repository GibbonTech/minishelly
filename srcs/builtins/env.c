/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:10:25 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 01:10:27 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minishell *minishell)
{
	t_envar	*current;

	current = minishell->env_list;
	while (current)
	{
		ft_putstr_fd(current->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(current->value, 1);
		current = current->next;
	}
	return (0);
}
