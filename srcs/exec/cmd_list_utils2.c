/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:36:49 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 02:01:19 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd_list;
	while (current)
	{
		next = current->next_cmd;
		free(current->cmd_name);
		ft_free_table(current->cmd_args);
		free(current);
		current = next;
	}
}

void	ft_free_table(char **table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (table[i] != NULL)
	{
		free(table[i]);
		table[i] = NULL;
		i++;
	}
	free(table);
}

bool	ft_process_cmd_list(char *cmd_cell, t_minishell *minishell)
{
	char	**cmd_args;

	cmd_args = ft_split_cmd_args(cmd_cell);
	if (!cmd_args)
		return (false);
	return (ft_create_cmd(minishell, cmd_args));
}
