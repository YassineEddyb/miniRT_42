/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:13:28 by ael-bach          #+#    #+#             */
/*   Updated: 2022/09/11 13:57:32 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

int	len_2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

void	check_rgbstring(char *str)
{
	int		i;
	int		point;

	point = 0;
	i = 0;
	while (str[i++])
		if (str[i] == ',')
			point += 1;
	if (point != 2)
	{
		printf("Error 1\n");
		exit (1);
	}
}

t_ambient	*ambient_light(char **str)
{
	t_ambient	*ambient;
	char		**rgb;

	if (len_2d(str) != 3)
		error("ERROR: AMBIENT");
	ambient = malloc (sizeof(t_ambient));
	ambient->ratio = ft_atof(str[1]);
	check_rgbstring(str[2]);
	rgb = ft_split(str[2], ',');
	ambient->rgb.red = ft_atof(rgb[0]);
	ambient->rgb.green = ft_atof(rgb[1]);
	ambient->rgb.blue = ft_atof(rgb[2]);
	free_two_arr(rgb);
	check_rgb_value(ambient->rgb);
	is_between(0.0, 1.0, ambient->ratio);
	return (ambient);
}
