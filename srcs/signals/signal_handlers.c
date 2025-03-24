/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:00:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/24 15:46:22 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal_parent(int num)
{
	if (num == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		g_exit_codes = 131;
	}
	else
		g_exit_codes = num + 128;
}

void	ft_sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_codes = 130;
}

void	ft_sigint_child_handler(int sig)
{
	(void)sig;
	g_exit_codes = 130;
	exit(g_exit_codes);
}

void	ft_heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\n", 1);
	close(STDIN_FILENO);
	g_exit_codes = 130;
}

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}
