/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:55:47 by ael-bach          #+#    #+#             */
/*   Updated: 2021/11/17 23:56:57 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_calclen(long num, int neg)
{
	long	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num /= 10;
	}
	if (neg < 0)
		return (len + 1);
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	int		len;
	long	n;

	if (nbr == 0)
		return (ft_strdup("0"));
	n = nbr;
	if (n < 0)
		n *= -1;
	len = ft_calclen(n, nbr);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (n != 0)
	{
		len--;
		str[len] = (n % 10) + '0';
		n /= 10;
		if (nbr < 0)
			str[0] = '-';
	}
	return (str);
}
