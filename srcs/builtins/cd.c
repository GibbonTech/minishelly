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

int	ft_update_pwd(t_minishell *minishell)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;
	int		result;

	if (!getcwd(cwd, PATH_MAX))
		return (0);
	old_pwd = ft_getenv("PWD", minishell);
	if (old_pwd)
	{
		result = ft_add_envar(minishell, "OLDPWD", old_pwd);
		free(old_pwd);
		if (!result)
			return (0);
	}
	return (ft_add_envar(minishell, "PWD", cwd));
}

int	ft_cd_previous(t_minishell *minishell)
{
	char	*path;
	int		result;

	path = ft_getenv("OLDPWD", minishell);
	if (!path)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		free(path);
		return (1);
	}
	ft_putendl_fd(path, 1);
	result = ft_update_pwd(minishell);
	free(path);
	if (result)
		return (0);
	else
		return (1);
}

int	ft_change_dir(t_minishell *minishell, char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	if (!ft_update_pwd(minishell))
	{
		ft_putendl_fd("minishell: cd: error updating PWD", 2);
		return (1);
	}
	return (0);
}

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

int	ft_cd(t_minishell *minishell, char **args)
{
	if (!args[1] || ft_strncmp(args[1], "--", 3) == 0)
		return (ft_cd_home(minishell));
	else if (ft_strncmp(args[1], "-", 2) == 0)
		return (ft_cd_previous(minishell));
	else
		return (ft_change_dir(minishell, args[1]));
}
