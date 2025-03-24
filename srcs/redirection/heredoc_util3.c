/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:00:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 20:11:29 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setup_heredoc_input(t_command *cmd, char *file)
{
	int	read_fd;

	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	read_fd = open(file, O_RDONLY);
	if (read_fd == -1)
	{
		unlink(file);
		free(file);
		return (0);
	}
	cmd->input_fd = read_fd;
	unlink(file);
	free(file);
	return (1);
}

static void	ft_heredoc_child_process(int fd, char *delimiter,
		t_minishell *minishell)
{
	char	*line;

	ft_setup_heredoc_signals();
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			ft_putendl_fd("minishell: warning: here-document delimited by", 2);
			ft_putendl_fd("end-of-file", 2);
			break ;
		}
		if (ft_check_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_process_heredoc_line(&line, minishell);
		ft_write_heredoc(fd, line);
		free(line);
	}
	close(fd);
	exit(0);
}

static int	ft_handle_heredoc_completion(pid_t pid, t_minishell *minishell,
		int original_status)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	ft_setup_interactive_signals();
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			minishell->exit_status = 130;
			return (0);
		}
		minishell->exit_status = 128 + WTERMSIG(status);
		return (0);
	}
	minishell->exit_status = original_status;
	return (1);
}

int	ft_read_heredoc(int fd, char *delimiter, t_minishell *minishell)
{
	pid_t	pid;
	int		original_status;

	original_status = minishell->exit_status;
	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("minishell: fork error in heredoc", 2);
		return (0);
	}
	if (pid == 0)
	{
		ft_heredoc_child_process(fd, delimiter, minishell);
		exit(1);
	}
	return (ft_handle_heredoc_completion(pid, minishell, original_status));
}
