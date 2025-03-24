/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:15:00 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/23 20:13:30 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Set command name
 * @param cmd Command structure
 * @param cmd_name Command name
 * @return true if successful, false otherwise
 */
static bool	ft_set_command_name(t_command *cmd, char *cmd_name)
{
	if (cmd_name)
	{
		cmd->cmd_name = ft_strdup(cmd_name);
		if (!cmd->cmd_name)
			return (false);
	}
	return (true);
}

/**
 * Count number of arguments
 * @param cmd_args Array of command arguments
 * @return Number of arguments
 */
static int	ft_count_args(char **cmd_args)
{
	int	arg_count;

	arg_count = 0;
	if (cmd_args)
	{
		while (cmd_args[arg_count])
			arg_count++;
	}
	return (arg_count);
}

/**
 * Allocate and set command arguments
 * @param cmd Command structure
 * @param cmd_args Command arguments
 * @param arg_count Number of arguments
 * @return true if successful, false otherwise
 */
static bool	ft_set_command_args(t_command *cmd, char **cmd_args, int arg_count)
{
	int	i;

	cmd->cmd_args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->cmd_args)
		return (false);
	i = 0;
	while (i < arg_count)
	{
		cmd->cmd_args[i] = ft_strdup(cmd_args[i]);
		if (!cmd->cmd_args[i])
		{
			while (--i >= 0)
				free(cmd->cmd_args[i]);
			free(cmd->cmd_args);
			return (false);
		}
		i++;
	}
	cmd->cmd_args[arg_count] = NULL;
	return (true);
}

/**
 * Set up the command structure with arguments
 * @param cmd Command structure to set up
 * @param cmd_name Command name
 * @param cmd_args Command arguments
 * @return true if successful, false otherwise
 */
static bool	ft_setup_command(t_command *cmd, char *cmd_name, char **cmd_args)
{
	int	arg_count;

	if (!ft_set_command_name(cmd, cmd_name))
		return (false);
	arg_count = ft_count_args(cmd_args);
	if (arg_count > 0)
	{
		if (!ft_set_command_args(cmd, cmd_args, arg_count))
		{
			if (cmd->cmd_name)
				free(cmd->cmd_name);
			return (false);
		}
	}
	return (true);
}

/**
 * Create a command structure with name and arguments
 * @param cmd_name Command name
 * @param cmd_args Command arguments
 * @return New command structure or NULL on error
 */
t_command	*ft_create_command_struct(char *cmd_name, char **cmd_args)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	if (!ft_init_command(cmd))
	{
		free(cmd);
		return (NULL);
	}
	if (!ft_setup_command(cmd, cmd_name, cmd_args))
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}
