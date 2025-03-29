/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:15:50 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 14:15:50 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	character;
	unsigned char	*p;

	character = (unsigned char)c;
	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = character;
		i++;
	}
	return (s);
}
