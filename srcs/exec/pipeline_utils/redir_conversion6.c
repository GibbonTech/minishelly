/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_conversion6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:30:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 19:40:53 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_arg_data
{
	char	**cmd_args;
	t_token	**redir_tokens;
	t_token	**target_tokens;
	int		redir_count;
}			t_arg_data;

static bool	ft_build_new_args(char **new_args, t_arg_data *data)
{
	int	i;
	int	new_idx;

	i = 0;
	new_idx = 0;
	while (data->cmd_args[i])
	{
		if (!ft_is_redirection_arg(data->cmd_args[i], data->redir_tokens,
				data->target_tokens, data->redir_count))
		{
			new_args[new_idx] = ft_strdup(data->cmd_args[i]);
			if (!new_args[new_idx])
			{
				return (ft_free_partial_args(new_args, new_idx));
			}
			new_idx++;
		}
		i++;
	}
	new_args[new_idx] = NULL;
	return (true);
}

bool	ft_create_non_redir_args(t_command *cmd, t_token **redir_tokens,
		t_token **target_tokens, int redir_count)
{
	char		**new_args;
	int			arg_count;
	t_arg_data	data;

	data.cmd_args = cmd->cmd_args;
	data.redir_tokens = redir_tokens;
	data.target_tokens = target_tokens;
	data.redir_count = redir_count;
	arg_count = ft_count_non_redir_args(cmd->cmd_args, redir_tokens,
			target_tokens, redir_count);
	new_args = malloc(sizeof(char *) * (arg_count + 1));
	if (!new_args)
	{
		return (false);
	}
	if (!ft_build_new_args(new_args, &data))
	{
		return (false);
	}
	ft_free_cmd_args(cmd->cmd_args);
	cmd->cmd_args = new_args;
	return (true);
}
