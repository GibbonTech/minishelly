/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:41:38 by aistierl          #+#    #+#             */
/*   Updated: 2025/03/29 14:14:33 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*temporary;

	if (nmemb != 0 && (size > 4294967295 / nmemb))
		return (NULL);
	temporary = malloc(sizeof(char) * (nmemb * size));
	if (temporary == NULL)
		return (NULL);
	ft_bzero(temporary, (nmemb * size));
	return (temporary);
}
