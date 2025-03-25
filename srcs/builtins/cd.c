/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:59:20 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 01:01:32 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_pwd(t_minishell *minishell);
int	ft_cd_previous(t_minishell *minishell);
int	ft_change_dir(t_minishell *minishell, char *path);

int	ft_cd_home(t_minishell *minishell)
{
	char	*home;
	int		result;

	home = ft_getenv("HOME", minishell);
	if (!home)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	if (chdir(home) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(home, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		free(home);
		return (1);
	}
	result = ft_update_pwd(minishell);
	free(home);
	if (result)
		return (0);
	else
		return (1);
}

static int	ft_check_too_many_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	return (0);
}

int	ft_cd(t_minishell *minishell, char **args)
{
	if (ft_check_too_many_args(args))
		return (1);
	if (!args[1] || ft_strncmp(args[1], "--", 3) == 0)
		return (ft_cd_home(minishell));
	else if (ft_strncmp(args[1], "-", 2) == 0)
		return (ft_cd_previous(minishell));
	else
		return (ft_change_dir(minishell, args[1]));
}
