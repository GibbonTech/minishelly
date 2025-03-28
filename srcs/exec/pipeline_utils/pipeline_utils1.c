/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:45:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/28 17:49:58 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_commands(t_command *commands)
{
	int			count;
	t_command	*current;

	count = 0;
	current = commands;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	ft_setup_pipes(int pipe_fd[2], int *prev_pipe_fd, int i, int cmd_count)
{
	if (i < cmd_count - 1)
	{
		if (pipe(pipe_fd) == -1)
		{
			if (*prev_pipe_fd != -1)
				close(*prev_pipe_fd);
			return (-1);
		}
	}
	return (0);
}

static int	ft_handle_special_status(int last_valid_status)
{
	if (WIFEXITED(last_valid_status))
		return (WEXITSTATUS(last_valid_status));
	else if (WIFSIGNALED(last_valid_status))
	{
		if (WTERMSIG(last_valid_status) == SIGQUIT)
		{
			write(STDERR_FILENO, "^\\", 2);
			write(STDERR_FILENO, "Quit (core dumped)\n", 18);
		}
		return (128 + WTERMSIG(last_valid_status));
	}
	return (last_valid_status);
}

static int	ft_check_last_command(pid_t *pids, int cmd_count)
{
	int	i;

	i = cmd_count;
	while (i-- >= 0)
	{
		if (pids[i] == -1)
			return (127);
		else if (pids[i] > 0)
			break ;
	}
	return (-1);
}

int	ft_wait_for_processes(pid_t *pids, int cmd_count)
{
	int		status;
	int		last_valid_status;
	int		completed;
	pid_t	pid;
	int		cmd_status;

	status = 0;
	last_valid_status = 0;
	completed = 0;
	while (completed < cmd_count)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > 0)
		{
			last_valid_status = status;
			completed++;
		}
		else if (pid == -1)
			break ;
	}
	cmd_status = ft_check_last_command(pids, cmd_count);
	if (cmd_status != -1)
		return (cmd_status);
	return (ft_handle_special_status(last_valid_status));
}
