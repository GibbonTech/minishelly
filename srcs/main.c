/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:00:00 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/24 18:37:42 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_exit_codes = 0;

/* External functions from main_utils.c and main_utils2.c */
int						ft_init_minishell_struct(t_minishell **minishell);
int						ft_prepare_commands(t_minishell *minishell,
							char *input);
int						ft_execute_and_cleanup(t_minishell *minishell);
void					ft_cleanup_env_vars(t_minishell *minishell);
void					ft_cleanup_data_structures(t_minishell *minishell);
void					ft_reset_command_lists(t_minishell *minishell);
int						ft_check_terminal(void);
int						ft_handle_input(char **input);
int						ft_run_shell_loop(t_minishell *minishell);

int	initialize_minishell(t_minishell **minishell, char **envp)
{
	if (!ft_check_terminal())
		return (0);
	if (!ft_init_minishell_struct(minishell))
		return (0);
	if (!ft_envar_list(envp, *minishell))
	{
		free(*minishell);
		return (0);
	}
	return (1);
}

int	process_input(t_minishell *minishell, char *input)
{
	char	*processed_input;
	
	processed_input = ft_insert_spaces_around_operators(input);
	if (!processed_input)
		return (0);
	if (!ft_parsing(minishell, processed_input))
	{
		ft_free_token_list(minishell);
		free(processed_input);
		return (1);
	}
	ft_reset_command_lists(minishell);
	if (!ft_prepare_commands(minishell, processed_input))
	{
		free(processed_input);
		return (0);
	}
	minishell->exit_status = ft_execute_and_cleanup(minishell);
	free(processed_input);
	return (1);
}

void	ft_cleanup_minishell(t_minishell *minishell)
{
	ft_cleanup_env_vars(minishell);
	ft_cleanup_data_structures(minishell);
	if (minishell)
		free(minishell);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*minishell;

	(void)ac;
	(void)av;
	if (!initialize_minishell(&minishell, envp))
		return (1);
	ft_setup_interactive_signals();
	ft_run_shell_loop(minishell);
	ft_cleanup_minishell(minishell);
	ft_reset_signals();
	rl_clear_history();
	return (g_exit_codes);
}
