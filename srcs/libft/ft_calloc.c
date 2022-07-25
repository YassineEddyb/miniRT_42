/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:56:37 by ael-bach          #+#    #+#             */
/*   Updated: 2021/11/18 18:21:46 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			i;

	p = malloc(size * count);
	if (!p)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		p[i] = '\0';
		i++;
	}
	return (p);
}
