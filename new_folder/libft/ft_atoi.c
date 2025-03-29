/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:13:33 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 14:14:12 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	char	*convert;
	int		i;
	int		sign;
	int		digit;

	i = 0;
	sign = 1;
	digit = 0;
	convert = (char *)nptr;
	while ((convert[i] >= '\t' && convert[i] <= '\r') || convert[i] == ' ')
		i++;
	if (convert[i] == '-' || convert[i] == '+')
	{
		if (convert[i] == '-')
			sign *= -1;
		i++;
	}
	if (convert[i] == '-' || convert[i] == '+')
		return (0);
	while (convert[i] >= '0' && convert[i] <= '9')
	{
		digit = digit * 10 + (convert[i] - '0');
		i++;
	}
	return (digit * sign);
}
