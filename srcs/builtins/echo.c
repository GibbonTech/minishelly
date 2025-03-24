/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:10:11 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/24 15:39:09 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_n_flag(char *arg)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 0;
	if (arg[i] != '-')
		return (n_flag);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		n_flag = 1;
	return (n_flag);
}

static void	ft_echo_print_args(char **args, int n_flag, int i)
{
	char	*unquoted;

	if (!args[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		unquoted = ft_remove_quotes_from_str(args[i]);
		if (unquoted)
		{
			ft_putstr_fd(unquoted, STDOUT_FILENO);
			free(unquoted);
		}
		else
			ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	if (!args || !args[0])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	i = 1;
	n_flag = 0;
	while (args[i] && ft_is_n_flag(args[i]))
	{
		n_flag = 1;
		i++;
	}
	ft_echo_print_args(args, n_flag, i);
	return (0);
}
