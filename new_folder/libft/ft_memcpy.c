/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:15:38 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 14:15:39 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*point_a;
	unsigned char	*point_b;
	unsigned int	i;

	if (src == NULL && dst == NULL)
		return (dst);
	point_a = (unsigned char *)src;
	point_b = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		point_b[i] = point_a[i];
		i++;
	}
	return (dst);
}
