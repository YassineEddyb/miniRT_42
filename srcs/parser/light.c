/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:10:35 by ael-bach          #+#    #+#             */
/*   Updated: 2022/07/22 15:16:54 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

t_light	*light(char **info)
{
	t_light		*light;
	char		**xyz;

	if (len_2d(info) != 4)
		error("ERROR: LIGHT");
	light = malloc (sizeof(t_light));
	check_rgbstring(info[1]);
	check_rgbstring(info[3]);
	xyz = ft_split(info[1], ',');
	light->pos.x = ft_atof(xyz[0]);
	light->pos.y = ft_atof(xyz[1]);
	light->pos.z = ft_atof(xyz[2]);
	free_two_arr(xyz);
	light->ratio = ft_atof(info[2]);
	xyz = ft_split(info[3], ',');
	light->rgb.red = ft_atoi(xyz[0]);
	light->rgb.green = ft_atoi(xyz[1]);
	light->rgb.blue = ft_atoi(xyz[2]);
	free_two_arr(xyz);
	return (light);
}