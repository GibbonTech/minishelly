/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:10:15 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/25 10:35:25 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_minishell_struct(t_minishell **minishell)
{
	*minishell = malloc(sizeof(t_minishell));
	if (!(*minishell))
		return (0);
	(*minishell)->token_list = NULL;
	(*minishell)->env_list = NULL;
	(*minishell)->cmd_list = NULL;
	(*minishell)->commands = NULL;
	(*minishell)->exit_status = 0;
	return (1);
}

int	ft_prepare_commands(t_minishell *minishell, char *input)
{
	if (!ft_cmd_struct(input, minishell))
	{
		ft_free_token_list(minishell);
		return (0);
	}
	if (!ft_convert_to_commands_with_redir(minishell))
	{
		ft_free_token_list(minishell);
		ft_free_cmd_list(minishell->cmd_list);
		minishell->cmd_list = NULL;
		return (0);
	}
	return (1);
}

int	ft_execute_and_cleanup(t_minishell *minishell)
{
	int	status;

	ft_setup_exec_signals();
	status = ft_execute_pipeline_with_redir(minishell);
	ft_setup_interactive_signals();
	ft_free_token_list(minishell);
	ft_free_cmd_list(minishell->cmd_list);
	minishell->cmd_list = NULL;
	ft_free_command_list(minishell);
	return (status);
}

void	ft_cleanup_env_vars(t_minishell *minishell)
{
	t_envar	*current;
	t_envar	*next;

	if (minishell->env_list)
	{
		current = minishell->env_list;
		while (current)
		{
			next = current->next;
			if (current->key)
				free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			current = next;
		}
	}
}
