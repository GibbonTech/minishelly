/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:16:54 by ykhomsi           #+#    #+#             */
/*   Updated: 2025/03/29 14:16:55 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char				*new;
	unsigned int		i;

	new = ft_strdup(s);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(new))
	{
		new[i] = f(i, new[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
