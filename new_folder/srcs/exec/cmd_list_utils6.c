/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:36:49 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 00:00:26 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_check_simple_case(char *str, char **result)
{
	if (!ft_strchr(str, '$') && !ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
	{
		*result = ft_strdup(str);
		return (true);
	}
	return (false);
}

bool	ft_resize_if_needed(char **expanded, int j, int *needed_size)
{
	char	*new_buffer;
	int		new_size;

	if (j + 100 < *needed_size)
		return (true);
	new_size = *needed_size * 2;
	if (new_size <= 0)
		new_size = 2048;
	new_buffer = malloc(new_size);
	if (!new_buffer)
		return (false);
	ft_memcpy(new_buffer, *expanded, j);
	new_buffer[j] = '\0';
	free(*expanded);
	*expanded = new_buffer;
	*needed_size = new_size;
	return (true);
}

int	ft_copy_var_value(char **expanded, char *var_value, int j)
{
	int	len;

	if (!var_value)
		return (j);
	len = ft_strlen(var_value);
	ft_memcpy(*expanded + j, var_value, len);
	j += len;
	(*expanded)[j] = '\0';
	free(var_value);
	return (j);
}
