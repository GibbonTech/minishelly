/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:45:00 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/23 20:11:00 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirection_error(char *filename, char *error_msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR_FILENO);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

int	ft_input_redirection(char *filename, t_command *cmd)
{
	int	fd;

	if (!filename)
	{
		ft_putendl_fd("minishell: input redirection: null filename",
			STDERR_FILENO);
		return (-1);
	}
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_redirection_error(filename, NULL);
		return (-1);
	}
	cmd->input_fd = fd;
	return (0);
}

int	ft_output_redirection(char *filename, t_command *cmd)
{
	int	fd;

	if (!filename)
	{
		ft_putendl_fd("minishell: output redirection: null filename",
			STDERR_FILENO);
		return (-1);
	}
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_redirection_error(filename, NULL);
		return (-1);
	}
	cmd->output_fd = fd;
	return (0);
}

int	ft_append_redirection(char *filename, t_command *cmd)
{
	int	fd;

	if (!filename)
	{
		ft_putendl_fd("minishell: append redirection: null filename",
			STDERR_FILENO);
		return (-1);
	}
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_redirection_error(filename, NULL);
		return (-1);
	}
	cmd->output_fd = fd;
	return (0);
}
