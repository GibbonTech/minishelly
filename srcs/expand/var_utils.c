/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:45:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 22:22:40 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*ft_get_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i;
	while (str[*i] && ft_is_var_char(str[*i]))
		(*i)++;
	len = *i - start;
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, str + start, len + 1);
	return (var_name);
}

char	*ft_expand_var(t_minishell *minishell, char *var_name)
{
	char	*result;

	if (!var_name || !*var_name)
		return (ft_strdup("$"));
	if (ft_strncmp(var_name, "?", 2) == 0)
		return (ft_itoa(minishell->exit_status));
	result = ft_getenv(var_name, minishell);
	return (result);
}

static int	ft_getenv_value(char *key, t_minishell *minishell, char **dest)
{
	t_envar	*current;

	if (!key || !minishell || !dest)
		return (0);
	*dest = NULL;
	current = minishell->env_list;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			*dest = ft_strdup(current->value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

char	*ft_getenv(char *key, t_minishell *minishell)
{
	char	*value;

	if (!key || !minishell)
		return (NULL);
	if (!ft_getenv_value(key, minishell, &value))
		return (NULL);
	return (value);
}
