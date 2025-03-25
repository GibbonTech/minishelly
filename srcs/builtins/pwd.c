/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:35:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/25 15:01:21 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_pwd_warning(char *opt)
{
	ft_putstr_fd("minishell: pwd: ", 2);
	ft_putstr_fd(opt, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("pwd: usage: pwd [-LP]\n", 2);
}

static int	ft_check_pwd_options(char **args)
{
	int	i;

	i = 1;
	while (args && args[i])
	{
		if (args[i][0] == '-' && args[i][1] != '\0')
		{
			if (ft_strncmp(args[i], "-L", 3) == 0 || ft_strncmp(args[i], "-P",
					3) == 0)
				i++;
			else
			{
				ft_print_pwd_warning(args[i]);
				return (1);
			}
		}
		else
			break ;
	}
	return (0);
}

int	ft_pwd(t_minishell *minishell)
{
	char	cwd[1024];

	if (ft_check_pwd_options(minishell->commands->cmd_args))
		return (1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}
