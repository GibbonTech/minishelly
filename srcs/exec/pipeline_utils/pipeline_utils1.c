/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:45:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/25 16:23:32 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_commands(t_command *commands)
{
	int			count;
	t_command	*current;

	count = 0;
	current = commands;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	ft_setup_pipes(int pipe_fd[2], int *prev_pipe_fd, int i, int cmd_count)
{
	(void)prev_pipe_fd;
	if (i < cmd_count - 1)
	{
		if (pipe(pipe_fd) == -1)
			return (-1);
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

int	ft_wait_for_processes(pid_t *pids, int cmd_count)
{
	int	status;
	int	i;
	int	last_valid_status;

	status = 0;
	last_valid_status = 0;
	i = 0;
	while (i < cmd_count)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			last_valid_status = status;
		}
		else if (pids[i] == -1 && i == cmd_count - 1)
			return (127);
		i++;
	}
	return (ft_handle_special_status(last_valid_status));
}
