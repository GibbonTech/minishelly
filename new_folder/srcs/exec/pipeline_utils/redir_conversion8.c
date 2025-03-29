/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_conversion8.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:33:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/27 07:32:21 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_handle_empty_command_list(t_minishell *minishell)
{
	t_command	*new_cmd;

	if (!minishell->token_list)
		return (true);
	new_cmd = ft_create_command_struct("", NULL);
	if (!new_cmd)
		return (false);
	if (!ft_add_command(minishell, new_cmd))
	{
		ft_delete_command(new_cmd);
		return (false);
	}
	return (true);
}
