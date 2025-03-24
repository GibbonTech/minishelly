/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:15:00 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/23 20:13:30 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Create a new redirection structure
 * @param type Type of redirection
 * @param filename Filename for redirection
 * @return New redirection structure or NULL on error
 */
t_redir	*ft_create_redirection(t_redir_type type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->next = NULL;
	if (filename)
	{
		redir->filename = ft_strdup(filename);
		if (!redir->filename)
		{
			free(redir);
			return (NULL);
		}
	}
	else
		redir->filename = NULL;
	return (redir);
}

/**
 * Add a redirection to a command
 * @param cmd Command to add redirection to
 * @param type Type of redirection
 * @param filename Filename for redirection
 * @return true if successful, false otherwise
 */
bool	ft_add_redirection(t_command *cmd, t_redir_type type, char *filename)
{
	t_redir	*new_redir;
	t_redir	*last;

	new_redir = ft_create_redirection(type, filename);
	if (!new_redir)
		return (false);
	if (!cmd->redirections)
		cmd->redirections = new_redir;
	else
	{
		last = cmd->redirections;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
	return (true);
}
