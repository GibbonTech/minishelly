/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:00:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/24 15:46:40 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setup_interactive_signals(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = ft_sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	ft_setup_exec_signals(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_signal_parent;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	memset(&sb, 0, sizeof(sb));
	sb.sa_handler = handle_signal_parent;
	sb.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sb, NULL);
}

void	ft_setup_heredoc_signals(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = ft_sigint_child_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}

void	ft_reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}
