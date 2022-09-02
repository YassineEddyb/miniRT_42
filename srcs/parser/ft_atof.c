/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:11:43 by ael-bach          #+#    #+#             */
/*   Updated: 2022/09/02 17:09:25 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

int	check_befor_atof(char *str)
{
	int		i;
	int		point;

	if (!str)
		error("ERROR : Missing element");
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

double	atof_part2(char **n_sp, int v, int n)
{
	int	v1;
	int	len;

	v1 = ft_atoi(n_sp[1]);
	len = ft_strlen(n_sp[1]);
	free_two_arr(n_sp);
	return ((v + (v1 / pow(10, len))) * n);
}

double	ft_atof(char *str)
{
	char	**n_sp;
	t_v		v;

	v.n = 1;
	v.c = 0;
	v.i = 0;
	check_befor_atof(str);
	while (str[v.i] == '+' || str[v.i] == '-')
	{
		if (str[v.i] == '+' || str[v.i] == '-')
			v.c += 1;
		if (str[v.i] == '-')
			v.n *= -1;
		v.i++;
	}
	n_sp = ft_split(str + v.i, '.');
	if (v.c >= 2 || (len_2d(n_sp) == 1 && check_befor_atof(str) > 0))
		error("ERROR : ATOF");
	v.v = ft_atoi(n_sp[0]);
	if (n_sp[1])
		return (atof_part2(n_sp, v.v, v.n));
	free_two_arr(n_sp);
	return (v.v * v.n);
}
