/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils7.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:36:49 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 02:02:13 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_process_cmd_name(t_cmd *new_cmd, char **expanded_args)
{
	if (expanded_args[0])
	{
		if (expanded_args[0][0] == '>' || expanded_args[0][0] == '<')
			new_cmd->cmd_name = ft_strdup("");
		else
			new_cmd->cmd_name = ft_strdup(expanded_args[0]);
	}
	else
		new_cmd->cmd_name = ft_strdup("");
	if (!new_cmd->cmd_name)
	{
		ft_free_table(expanded_args);
		free(new_cmd);
		return (false);
	}
	return (true);
}

static void	ft_add_cmd_to_list(t_minishell *minishell, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!minishell->cmd_list)
		minishell->cmd_list = new_cmd;
	else
	{
		current = minishell->cmd_list;
		while (current->next_cmd)
			current = current->next_cmd;
		current->next_cmd = new_cmd;
	}
}

bool	ft_create_cmd(t_minishell *minishell, char **cmd_args)
{
	t_cmd	*new_cmd;
	char	**expanded_args;

	if (!ft_init_cmd_creation(minishell, cmd_args, &new_cmd, &expanded_args))
		return (false);
	if (cmd_args)
		ft_free_table(cmd_args);
	if (!ft_process_cmd_name(new_cmd, expanded_args))
		return (false);
	new_cmd->cmd_args = expanded_args;
	new_cmd->next_cmd = NULL;
	ft_add_cmd_to_list(minishell, new_cmd);
	return (true);
}
