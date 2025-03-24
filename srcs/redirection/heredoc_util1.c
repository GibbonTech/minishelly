/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:00:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 20:11:57 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_heredoc(int fd, char *line)
{
	if (line)
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static char	*ft_get_heredoc_var_internal(char *var_name, t_minishell *minishell)
{
	char	*var_value;
	t_envar	*env;

	if (!var_name)
		return (NULL);
	if (ft_strncmp(var_name, "?", 2) == 0)
	{
		return (ft_itoa(minishell->exit_status));
	}
	env = minishell->env_list;
	while (env)
	{
		if (ft_strncmp(env->key, var_name, ft_strlen(var_name) + 1) == 0)
		{
			if (env->value)
				var_value = ft_strdup(env->value);
			else
				var_value = ft_strdup("");
			return (var_value);
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*ft_get_heredoc_var_value(char *var_name, t_minishell *minishell)
{
	return (ft_get_heredoc_var_internal(var_name, minishell));
}

int	ft_check_delimiter(char *line, char *delimiter)
{
	if (!line || !delimiter)
		return (0);
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
		&& ft_strlen(line) == ft_strlen(delimiter))
		return (1);
	return (0);
}
