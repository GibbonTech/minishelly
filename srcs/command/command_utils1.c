/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:15:00 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/28 23:57:44 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_init_command(t_command *cmd)
{
	if (!cmd)
		return (false);
	cmd->cmd_name = NULL;
	cmd->cmd_args = NULL;
	cmd->redirections = NULL;
	cmd->input_fd = STDIN_FILENO;
	cmd->output_fd = STDOUT_FILENO;
	cmd->next = NULL;
	return (true);
}

t_command	*ft_last_command(t_minishell *minishell)
{
	t_command	*current;

	if (!minishell->commands)
		return (NULL);
	current = minishell->commands;
	while (current->next)
		current = current->next;
	return (current);
}

bool	ft_add_command(t_minishell *minishell, t_command *cmd)
{
	t_command	*last;

	if (!minishell || !cmd)
		return (false);
	if (!minishell->commands)
		minishell->commands = cmd;
	else
	{
		last = ft_last_command(minishell);
		last->next = cmd;
	}
	return (true);
}

void	ft_free_redirection(t_redir *redir)
{
	if (redir)
	{
		if (redir->filename)
			free(redir->filename);
		free(redir);
	}
}
