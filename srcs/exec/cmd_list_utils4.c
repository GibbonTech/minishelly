/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:36:49 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/24 15:43:51 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_handle_exit_status(t_minishell *minishell, int *i)
{
	char	*var_value;

	var_value = ft_itoa(minishell->exit_status);
	(*i)++;
	return (var_value);
}

static char	*ft_get_env_value(t_minishell *minishell, char *var_name)
{
	t_envar	*current;
	char	*var_value;

	var_value = NULL;
	current = minishell->env_list;
	while (current)
	{
		if (ft_strncmp(current->key, var_name, ft_strlen(var_name) + 1) == 0)
		{
			if (current->value)
			{
				var_value = ft_strdup(current->value);
			}
			break ;
		}
		current = current->next;
	}
	if (!var_value)
	{
		var_value = ft_strdup("");
	}
	return (var_value);
}

char	*ft_expand_env_var_value(t_minishell *minishell, char *str, int *i)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *i;
	if (str[*i] == '?')
		return (ft_handle_exit_status(minishell, i));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (NULL);
	var_value = ft_get_env_value(minishell, var_name);
	free(var_name);
	return (var_value);
}

char	*ft_init_expansion(char *str, int *buffer_size)
{
	char	*expanded;
	size_t	str_len;

	str_len = ft_strlen(str);
	*buffer_size = str_len * 4 + 256;
	if (*buffer_size < 1024)
		*buffer_size = 1024;
	expanded = malloc(*buffer_size);
	if (!expanded)
		return (NULL);
	expanded[0] = '\0';
	return (expanded);
}
