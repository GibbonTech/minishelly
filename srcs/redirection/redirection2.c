/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:00:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 20:11:14 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_apply_redirections(t_command *cmd, t_minishell *minishell)
{
	t_redir	*redir;

	if (!cmd)
		return (-1);
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_INPUT && ft_input_redirection(redir->filename,
				cmd) == -1)
			return (-1);
		else if (redir->type == REDIR_OUTPUT
			&& ft_output_redirection(redir->filename, cmd) == -1)
			return (-1);
		else if (redir->type == REDIR_APPEND
			&& ft_append_redirection(redir->filename, cmd) == -1)
			return (-1);
		else if (redir->type == REDIR_HEREDOC && ft_process_heredoc(cmd,
				redir->filename, minishell) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

void	ft_redirect_io(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->input_fd != STDIN_FILENO)
	{
		dup2(cmd->input_fd, STDIN_FILENO);
		close(cmd->input_fd);
	}
	if (cmd->output_fd != STDOUT_FILENO)
	{
		dup2(cmd->output_fd, STDOUT_FILENO);
		close(cmd->output_fd);
	}
}
