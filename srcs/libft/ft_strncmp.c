/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:00:49 by ael-bach          #+#    #+#             */
/*   Updated: 2021/11/14 22:20:42 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ps1;
	unsigned char	*ps2;
	size_t			i;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	if (n <= 0)
		return (0);
	i = 0;
	if (ps1[i] == '\0' && ps2[i] == '\0')
		return (0);
	if (ps1[i] == '\0')
		return (-1);
	if (ps2[i] == '\0')
		return (1);
	while ((ps1[i] || ps2[i]) && i < n)
	{
		if (ps1[i] > ps2[i])
			return (ps1[i] - ps2[i]);
		if (ps1[i] < ps2[i])
			return (ps1[i] - ps2[i]);
		i++;
	}
	return (0);
}
