/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:44:45 by ael-bach          #+#    #+#             */
/*   Updated: 2021/11/13 22:35:23 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s_cast;
	int		i;
	char	c1;

	s_cast = (char *)s;
	c1 = (char)c;
	i = 0;
	while (s_cast[i])
	{
		i++;
	}
	while (i > 0 && s_cast[i] != c1)
	{
		i--;
	}
	if (s_cast[i] == c1)
	{
		return (s_cast + i);
	}
	return (0);
}
