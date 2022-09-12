/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:45:17 by ael-bach          #+#    #+#             */
/*   Updated: 2022/09/11 12:12:36 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	ft_line(const char *str, long i, long n)
{
	long long	a;

	a = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			a = a * 10 + (str[i] - 48);
			i++;
		}
		else
		{
			printf("ERROR\n");
			exit (1);
		}
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
	{
		printf("ERROR\n");
		exit (1);
	}
	else
		return (ft_line(str, i, n));
}
