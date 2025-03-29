/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:09:26 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/29 00:00:42 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_env_vars(t_minishell *minishell)
{
	t_envar	*current;
	int		count;

	count = 0;
	current = minishell->env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	*ft_create_env_string(char *key, char *value)
{
	char	*env_string;
	size_t	key_len;
	size_t	value_len;

	if (!key)
		return (NULL);
	key_len = ft_strlen(key);
	if (value)
		value_len = ft_strlen(value);
	else
		value_len = 0;
	env_string = malloc(key_len + value_len + 2);
	if (!env_string)
		return (NULL);
	ft_strlcpy(env_string, key, key_len + 1);
	ft_strlcat(env_string, "=", key_len + 2);
	if (value)
		ft_strlcat(env_string, value, key_len + value_len + 2);
	return (env_string);
}

char	**ft_env_to_array(t_minishell *minishell)
{
	char	**env_array;
	t_envar	*current;
	int		i;
	int		count;

	count = ft_count_env_vars(minishell);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = minishell->env_list;
	i = 0;
	while (current && i < count)
	{
		env_array[i] = ft_create_env_string(current->key, current->value);
		if (!env_array[i])
		{
			ft_free_env_array(env_array, i);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	ft_is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strncmp(cmd_name, "cd", 3) == 0 || ft_strncmp(cmd_name, "echo",
			5) == 0 || ft_strncmp(cmd_name, "env", 4) == 0
		|| ft_strncmp(cmd_name, "exit", 5) == 0 || ft_strncmp(cmd_name,
			"export", 7) == 0 || ft_strncmp(cmd_name, "pwd", 4) == 0
		|| ft_strncmp(cmd_name, "unset", 6) == 0)
		return (1);
	return (0);
}
