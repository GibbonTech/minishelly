/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:09:26 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/29 00:00:40 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_restore_io(int stdin_backup, int stdout_backup)
{
	if (stdin_backup != -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	if (stdout_backup != -1)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
}

int	ft_execute_builtin_with_redir(t_minishell *minishell, t_command *cmd,
		int stdin_backup, int stdout_backup)
{
	int	status;

	if (stdin_backup == -1 || stdout_backup == -1)
		return (1);
	if (ft_apply_redirections(cmd, minishell) == -1)
	{
		close(stdin_backup);
		close(stdout_backup);
		return (1);
	}
	ft_redirect_io(cmd);
	status = ft_execute_specific_builtin(minishell, cmd);
	ft_restore_io(stdin_backup, stdout_backup);
	return (status);
}

/* Handle empty command or command with redirections only */
static int	ft_handle_empty_command(t_minishell *minishell, t_command *cmd)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (ft_apply_redirections(cmd, minishell) == -1)
	{
		ft_restore_io(stdin_backup, stdout_backup);
		return (1);
	}
	ft_restore_io(stdin_backup, stdout_backup);
	return (0);
}

int	ft_execute_command_with_redir(t_minishell *minishell, t_command *cmd)
{
	char	*cmd_path;
	int		stdin_backup;
	int		stdout_backup;

	stdin_backup = -1;
	stdout_backup = -1;
	if (!cmd->cmd_name || !cmd->cmd_name[0])
		return (ft_handle_empty_command(minishell, cmd));
	if (ft_is_builtin(cmd->cmd_name))
	{
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
		return (ft_execute_builtin_with_redir(minishell, cmd, stdin_backup,
				stdout_backup));
	}
	cmd_path = ft_safe_find_command(cmd->cmd_name, minishell);
	if (!cmd_path)
		return (127);
	return (ft_execute_external_command(minishell, cmd, cmd_path));
}
