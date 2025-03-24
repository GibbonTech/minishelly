/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:15:00 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/23 20:13:30 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Initialize command structure with default values
 * @param cmd Command structure to initialize
 * @return true if successful, false otherwise
 */
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

/**
 * Get the last command in the list
 * @param minishell The minishell structure
 * @return Pointer to the last command
 */
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

/**
 * Add a command to the command list
 * @param minishell The minishell structure
 * @param cmd Command to add
 * @return true if successful, false otherwise
 */
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

/**
 * Free a redirection structure
 * @param redir Redirection structure to free
 */
void	ft_free_redirection(t_redir *redir)
{
	if (redir)
	{
		if (redir->filename)
			free(redir->filename);
		free(redir);
	}
}
