/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:11:43 by ael-bach          #+#    #+#             */
/*   Updated: 2022/08/29 21:35:07 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

int	check_befor_atof(char *str)
{
	int i;
	int point;

	if (!str)
		error("ERROR : GHYRHA");
	point = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			point += 1;
		i++;
	}
    if (point > 1)
    {
		printf("Error\n");
		exit (1);
    }
	return (point);
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
	if (c >= 2 || (len_2d(n_sp) == 1 && check_befor_atof(str) > 0))
		error("ERROR : ATOF");
	if (n_sp[1])
		return ((ft_atoi(n_sp[0]) + (ft_atoi(n_sp[1])
				/ pow(10, ft_strlen(n_sp[1]))) ) * n);
	return (ft_atoi(n_sp[0])  * n);
}