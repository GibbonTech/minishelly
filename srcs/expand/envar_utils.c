/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:22:15 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 22:22:16 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Extract key from environment variable string
 * @param envar Environment variable string
 * @param delimiter Delimiter character (usually '=')
 * @return Allocated key string or NULL on error
 */
char	*ft_get_key(char *envar, char delimiter)
{
	int		i;
	char	*key;

	i = 0;
	while (envar[i] && envar[i] != delimiter)
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, envar, i + 1);
	return (key);
}

/**
 * Extract value from environment variable string
 * @param envar Environment variable string
 * @param start Starting position for value
 * @return Allocated value string or NULL on error
 */
char	*ft_get_value(char *envar, int start)
{
	if (!envar[start])
		return (ft_strdup(""));
	return (ft_strdup(envar + start));
}

/**
 * Create environment variable list from envp array
 * @param envp Environment variables array
 * @param minishell The minishell structure
 * @return true if successful, false otherwise
 */
bool	ft_envar_list(char **envp, t_minishell *minishell)
{
	int		i;
	char	*key;
	char	*value;
	bool	result;

	i = 0;
	while (envp[i])
	{
		key = ft_get_key(envp[i], '=');
		if (!key)
			return (false);
		value = ft_get_value(envp[i], ft_strlen(key) + 1);
		if (!value)
		{
			free(key);
			return (false);
		}
		result = ft_add_envar(minishell, key, value);
		free(key);
		free(value);
		if (!result)
			return (false);
		i++;
	}
	return (true);
}
