/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:32:05 by ael-bach          #+#    #+#             */
/*   Updated: 2021/11/13 22:58:08 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ps;
	unsigned char	c1;
	size_t			i;

	ps = (unsigned char *)s;
	c1 = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ps[i] == c1)
			return (ps + i);
		i++;
	}
	return (0);
}
