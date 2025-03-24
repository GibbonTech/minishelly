/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:30:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 16:35:59 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_external_command(t_minishell *minishell, t_command *cmd,
	char *cmd_path)
{
	pid_t	pid;
	int		status;

	ft_setup_exec_signals();
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		return (1);
	}
	if (pid == 0)
	{
		ft_child_process_setup(cmd, cmd_path, minishell);
		exit(1);
	}
	status = ft_wait_for_child(pid);
	free(cmd_path);
	return (status);
}
