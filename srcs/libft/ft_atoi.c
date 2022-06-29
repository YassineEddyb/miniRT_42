/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:45:17 by ael-bach          #+#    #+#             */
/*   Updated: 2021/11/18 19:27:45 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_line(const char *str, long i, long n)
{
	long long	a;

	a = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + (str[i] - 48);
		i++;
	}
	return (a * n);
}

int	ft_atoi(const char *str)
{
	long long		i;
	long long		n;
	long long		c;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	n = 1;
	c = 0;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '+' || str[i] == '-')
			c += 1;
		if (str[i] == '-')
			n *= -1;
		i++;
	}
	if (c >= 2)
		return (0);
	else
		return (ft_line(str, i, n));
}
