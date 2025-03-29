/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:36:10 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 00:00:18 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_specific_builtin(t_minishell *minishell, t_command *cmd)
{
	int	status;

	if (ft_strncmp(cmd->cmd_name, "echo", 5) == 0)
		status = ft_echo(cmd->cmd_args);
	else if (ft_strncmp(cmd->cmd_name, "cd", 3) == 0)
		status = ft_cd(minishell, cmd->cmd_args);
	else if (ft_strncmp(cmd->cmd_name, "pwd", 4) == 0)
		status = ft_pwd(minishell);
	else if (ft_strncmp(cmd->cmd_name, "export", 7) == 0)
		status = ft_export(minishell, cmd->cmd_args);
	else if (ft_strncmp(cmd->cmd_name, "unset", 6) == 0)
		status = ft_unset(minishell, cmd->cmd_args);
	else if (ft_strncmp(cmd->cmd_name, "env", 4) == 0)
		status = ft_env(minishell);
	else if (ft_strncmp(cmd->cmd_name, "exit", 5) == 0)
		status = ft_exit(minishell, cmd->cmd_args);
	else
		status = 1;
	return (status);
}

int	ft_handle_command_not_found(char *cmd_name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (127);
}
