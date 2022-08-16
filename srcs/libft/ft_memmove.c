/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:44:04 by ael-bach          #+#    #+#             */
/*   Updated: 2021/11/09 18:50:30 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*cast_dst;
	unsigned char		*cast_src;

	cast_dst = (unsigned char *)dst;
	cast_src = (unsigned char *)src;
	if (cast_src == '\0' && cast_dst == '\0')
		return (NULL);
	if (cast_src >= cast_dst)
	{
		ft_memcpy(cast_dst, cast_src, len);
	}
	if (cast_src < cast_dst)
	{
		i = len;
		while (i > 0)
		{
			i--;
			cast_dst[i] = cast_src[i];
		}
	}
	return (cast_dst);
}
