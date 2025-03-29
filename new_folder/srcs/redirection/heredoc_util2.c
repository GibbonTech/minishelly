/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:00:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 20:11:44 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_env_var(char **line, t_minishell *minishell, int i)
{
	char	*var_name;
	char	*var_value;
	char	*new_line;
	int		var_name_len;
	int		dollar_pos;

	dollar_pos = i;
	var_name = ft_get_var_name(*line, &i);
	if (!var_name)
		return ;
	var_name_len = ft_strlen(var_name);
	var_value = ft_get_heredoc_var_value(var_name, minishell);
	free(var_name);
	if (!var_value)
		return ;
	new_line = ft_replace_substr(*line, dollar_pos, var_name_len + 1,
			var_value);
	free(var_value);
	if (!new_line)
		return ;
	free(*line);
	*line = new_line;
}

void	ft_process_heredoc_line(char **line, t_minishell *minishell)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] && (*line)[i + 1] != ' '
			&& (*line)[i + 1] != '\t' && (*line)[i + 1] != '\n' && (*line)[i
			+ 1] != '$')
		{
			ft_expand_env_var(line, minishell, i + 1);
		}
		else
			i++;
	}
}

char	*ft_create_heredoc_file(int *count)
{
	char	*count_str;
	char	*file;

	count_str = ft_itoa((*count)++);
	if (!count_str)
		return (NULL);
	file = ft_strjoin("/tmp/heredoc_", count_str);
	free(count_str);
	return (file);
}

int	ft_open_heredoc_file(char *file, int *fd)
{
	*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*fd == -1)
	{
		free(file);
		return (0);
	}
	return (1);
}
