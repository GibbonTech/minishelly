/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:15:30 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/25 10:37:15 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cleanup_data_structures(t_minishell *minishell)
{
	if (minishell->token_list)
		ft_free_token_list(minishell);
	if (minishell->cmd_list)
		ft_free_cmd_list(minishell->cmd_list);
	if (minishell->commands)
		ft_free_command_list(minishell);
}

void	ft_reset_command_lists(t_minishell *minishell)
{
	if (minishell->cmd_list)
	{
		ft_free_cmd_list(minishell->cmd_list);
		minishell->cmd_list = NULL;
	}
	if (minishell->commands)
	{
		ft_free_command_list(minishell);
	}
}

int	ft_check_terminal(void)
{
	if (!isatty(STDIN_FILENO))
	{
		printf("Minishell requires a terminal. Do better.\n");
		return (0);
	}
	return (1);
}

int	ft_handle_input(char **input)
{
	*input = readline("minishell$ ");
	if (!*input)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (0);
	}
	if ((*input)[0] != '\0')
		add_history(*input);
	return (1);
}

int	ft_run_shell_loop(t_minishell *minishell)
{
	char	*input;
	int		result;

	result = 1;
	while (result)
	{
		if (!ft_handle_input(&input))
			break ;
		result = process_input(minishell, input);
		free(input);
		input = NULL;
		if (!result)
			break ;
	}
	return (result);
}
