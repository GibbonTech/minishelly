/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_numeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:11:05 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/23 01:11:06 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_process_digits(const char *s, int i, int neg, long *res)
{
	unsigned long long	num;
	int					error;

	num = 0;
	error = 0;
	while (s[i] && ft_isdigit(s[i]))
	{
		num = num * 10 + (s[i] - '0');
		if (neg == 1 && num > LONG_MAX)
		{
			error = 1;
			break ;
		}
		if (neg == -1 && num > ((unsigned long long)LONG_MAX + 1))
		{
			error = 1;
			break ;
		}
		i++;
	}
	if (s[i])
		error = 1;
	*res = (long)(neg * num);
	return (error);
}

long	ft_atol(const char *str, int *error)
{
	int		i;
	int		neg;
	long	result;

	i = 0;
	neg = 1;
	*error = 0;
	while (str[i] && ft_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	if (!str[i])
	{
		*error = 1;
		return (0);
	}
	*error = ft_process_digits(str, i, neg, &result);
	return (result);
}
