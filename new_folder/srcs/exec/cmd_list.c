/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:02:43 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 00:00:31 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_create_cmd_list(t_minishell *minishell, char **cmd_cells)
{
	int	i;

	i = 0;
	while (cmd_cells[i])
	{
		if (!ft_process_cmd_list(cmd_cells[i], minishell))
		{
			ft_free_cmd_list(minishell->cmd_list);
			minishell->cmd_list = NULL;
			return (false);
		}
		i++;
	}
	return (true);
}
