/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:06:57 by ael-bach          #+#    #+#             */
/*   Updated: 2021/11/04 19:23:45 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1cast;
	unsigned char	*s2cast;
	size_t			i;

	s1cast = (unsigned char *)s1;
	s2cast = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1cast[i] > s2cast[i])
			return (s1cast[i] - s2cast[i]);
		if (s1cast[i] < s2cast[i])
			return (s1cast[i] - s2cast[i]);
		i++;
	}
	return (0);
}
