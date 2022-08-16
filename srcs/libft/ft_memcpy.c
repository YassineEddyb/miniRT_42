/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:34:00 by ael-bach          #+#    #+#             */
/*   Updated: 2021/11/09 18:45:33 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dstcast;
	unsigned char	*srccast;
	size_t			i;

	dstcast = (unsigned char *)dst;
	srccast = (unsigned char *)src;
	if (dstcast == '\0' && srccast == '\0')
		return (NULL);
	i = 0;
	while (i < n)
	{
		dstcast[i] = srccast[i];
		i++;
	}
	return (dstcast);
}
