/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:49:47 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 00:14:15 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_cmd_args(char *cmd_cell)
{
	if (!cmd_cell)
		return (NULL);
	return (ft_split_with_quotes(cmd_cell, ' '));
}

bool	ft_cmd_struct(char *input, t_minishell *minishell)
{
	char	**cmd_cells;
	int		i;

	cmd_cells = ft_split_with_quotes(input, '|');
	if (!cmd_cells)
		return (false);
	i = 0;
	while (cmd_cells[i])
		i++;
	if (!ft_create_cmd_list(minishell, cmd_cells))
	{
		ft_free_table(cmd_cells);
		return (false);
	}
	ft_free_table(cmd_cells);
	return (true);
}
