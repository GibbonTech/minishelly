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

static int	ft_check_n_chars(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_is_n_flag(char *arg)
{
	char	*unquoted;
	int		result;

	if (!arg)
		return (0);
	unquoted = ft_remove_quotes_from_str(arg);
	if (!unquoted)
		return (0);
	if (unquoted[0] != '-' || (unquoted[0] == '-' && !unquoted[1]))
	{
		free(unquoted);
		return (0);
	}
	result = ft_check_n_chars(unquoted);
	free(unquoted);
	return (result);
}

static void	ft_print_arg(char *arg)
{
	char	*unquoted;

	unquoted = ft_remove_quotes_from_str(arg);
	if (unquoted)
	{
		ft_putstr_fd(unquoted, STDOUT_FILENO);
		free(unquoted);
	}
	else
		ft_putstr_fd(arg, STDOUT_FILENO);
}

static void	ft_echo_print_args(char **args, int n_flag, int i)
{
	if (!args[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_print_arg(args[i]);
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
