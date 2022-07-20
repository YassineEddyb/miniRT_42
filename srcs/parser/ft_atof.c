/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:11:43 by ael-bach          #+#    #+#             */
/*   Updated: 2022/07/20 19:56:21 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

void	check_befor_atof(char *str)
{
	int i;
	int point;

	point = 0;
	i = 0;
	while (str[i++])
		if (str[i] == '.')
			point += 1;
    if (point > 1)
    {
		printf("Error\n");
		exit (1);
    }
}

double	ft_atof(char *str)
{
	char	**n_sp;
	int		n;
	int		c;
	int		i;

	n = 1;
	c = 0;
	i = 0;
	check_befor_atof(str);
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '+' || str[i] == '-')
			c += 1;
		if (str[i] == '-')
			n *= -1;
		i++;
	}
	n_sp = ft_split(str + i, '.');
	if (c >= 2 || n_sp[2])
	{
		printf("Error\n");
		exit (1);
	}
	return ((ft_atoi(n_sp[0]) + (ft_atoi(n_sp[1])
			/ pow(10, ft_strlen(n_sp[1]))) ) * n);
}