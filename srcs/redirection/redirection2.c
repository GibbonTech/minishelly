/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:00:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 00:07:12 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_input_output(t_redir *redir, t_command *cmd)
{
	if (redir->type == REDIR_INPUT && ft_input_redirection(redir->filename,
			cmd) == -1)
		return (-1);
	else if (redir->type == REDIR_OUTPUT
		&& ft_output_redirection(redir->filename, cmd) == -1)
		return (-1);
	return (0);
}

static int	ft_handle_append_heredoc(t_redir *redir, t_command *cmd,
		t_minishell *minishell, bool heredoc_processed)
{
	if (redir->type == REDIR_APPEND
		&& ft_append_redirection(redir->filename, cmd) == -1)
		return (-1);
	else if (redir->type == REDIR_HEREDOC && !heredoc_processed
		&& ft_process_heredoc(cmd, redir->filename, minishell) == -1)
		return (-1);
	return (0);
}

static int	ft_handle_regular_redirections(t_redir *redir, t_command *cmd,
		t_minishell *minishell, bool heredoc_processed)
{
	while (redir)
	{
		if (ft_handle_input_output(redir, cmd) == -1
			|| ft_handle_append_heredoc(redir, cmd, minishell,
				heredoc_processed) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

int	ft_apply_redirections(t_command *cmd, t_minishell *minishell)
{
	t_redir	*redir;
	bool	heredoc_processed;

	if (!cmd)
		return (-1);
	heredoc_processed = false;
	if (ft_has_heredoc(cmd))
		heredoc_processed = (cmd->input_fd != STDIN_FILENO);
	redir = cmd->redirections;
	return (ft_handle_regular_redirections(redir, cmd, minishell,
			heredoc_processed));
}
