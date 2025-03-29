/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:15:00 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/28 23:57:43 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
