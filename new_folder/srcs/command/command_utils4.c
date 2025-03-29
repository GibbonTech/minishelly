/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:15:00 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/28 23:57:59 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_command_args(char **cmd_args)
{
	int	i;

	if (!cmd_args)
		return ;
	i = 0;
	while (cmd_args[i])
	{
		free(cmd_args[i]);
		i++;
	}
	free(cmd_args);
}

static void	ft_free_redirections(t_redir *redirections)
{
	t_redir	*current;
	t_redir	*next;

	current = redirections;
	while (current)
	{
		next = current->next;
		ft_free_redirection(current);
		current = next;
	}
}

void	ft_delete_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd_name)
		free(cmd->cmd_name);
	if (cmd->cmd_args)
		ft_free_command_args(cmd->cmd_args);
	if (cmd->redirections)
		ft_free_redirections(cmd->redirections);
	if (cmd->input_fd > 0 && cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	if (cmd->output_fd > 0 && cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	free(cmd);
}

void	ft_free_command_list(t_minishell *minishell)
{
	t_command	*current;
	t_command	*next;

	if (!minishell)
		return ;
	current = minishell->commands;
	while (current)
	{
		next = current->next;
		ft_delete_command(current);
		current = next;
	}
	minishell->commands = NULL;
}
