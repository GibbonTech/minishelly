/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:15:26 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/27 12:05:00 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env_array(char **env_array, int count)
{
	int	i;

	if (!env_array)
		return ;
	if (count < 0)
	{
		i = 0;
		while (env_array[i])
		{
			free(env_array[i]);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < count)
		{
			free(env_array[i]);
			i++;
		}
	}
	free(env_array);
}

char	*ft_check_full_path(char *cmd_name)
{
	if (cmd_name[0] == '/' || cmd_name[0] == '.')
	{
		if (access(cmd_name, X_OK) == 0)
			return (ft_strdup(cmd_name));
	}
	return (NULL);
}

char	*ft_check_dir_for_cmd(char *dir, char *cmd_name)
{
	char	*cmd_path;

	cmd_path = malloc(ft_strlen(dir) + ft_strlen(cmd_name) + 2);
	if (!cmd_path)
		return (NULL);
	ft_strlcpy(cmd_path, dir, ft_strlen(dir) + 1);
	ft_strlcat(cmd_path, "/", ft_strlen(dir) + 2);
	ft_strlcat(cmd_path, cmd_name, ft_strlen(dir) + ft_strlen(cmd_name) + 2);
	if (access(cmd_path, X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

/**
 * Check all directories for a command
 * @param path_dirs Array of path directories to check
 * @param cmd_name Command name to search for
 * @return Path to the command if found, NULL otherwise
 */
static char	*ft_check_all_dirs_for_cmd(char **path_dirs, char *cmd_name)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		cmd_path = ft_check_dir_for_cmd(path_dirs[i], cmd_name);
		if (cmd_path)
		{
			ft_free_table(path_dirs);
			return (cmd_path);
		}
		i++;
	}
	ft_free_table(path_dirs);
	return (NULL);
}

char	*ft_find_command(char *cmd_name, t_minishell *minishell)
{
	char	*cmd_path;
	char	*path_var;
	char	**path_dirs;

	if (!cmd_name || !*cmd_name)
		return (NULL);
	cmd_path = ft_check_full_path(cmd_name);
	if (cmd_path)
		return (cmd_path);
	path_var = ft_getenv("PATH", minishell);
	if (!path_var)
		return (NULL);
	path_dirs = ft_split(path_var, ':');
	free(path_var);
	if (!path_dirs)
		return (NULL);
	return (ft_check_all_dirs_for_cmd(path_dirs, cmd_name));
}
