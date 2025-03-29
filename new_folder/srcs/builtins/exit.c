/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:15:08 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 01:15:21 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_exit(t_minishell *minishell, int status)
{
	ft_cleanup_minishell(minishell);
	rl_clear_history();
	exit(status);
}

static void	ft_process_exit_arg(t_minishell *minishell, char **args)
{
	long	status;
	int		error;
	int		code;

	error = 0;
	status = ft_atol(args[1], &error);
	if (error)
	{
		code = 2;
		ft_print_numeric_error("exit", args[1], "numeric argument required",
			&code);
		ft_clean_exit(minishell, 2);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		minishell->exit_status = 1;
		return ;
	}
	ft_clean_exit(minishell, status % 256);
}

int	ft_exit(t_minishell *minishell, char **args)
{
	int	code;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!args[1])
		ft_clean_exit(minishell, minishell->exit_status);
	if (!ft_is_numeric(args[1]))
	{
		code = 2;
		ft_print_numeric_error("exit", args[1], "numeric argument required",
			&code);
		ft_clean_exit(minishell, 2);
	}
	ft_process_exit_arg(minishell, args);
	return (minishell->exit_status);
}
