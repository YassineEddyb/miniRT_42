/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:55:28 by ael-bach          #+#    #+#             */
/*   Updated: 2022/08/16 17:17:32 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

t_cy	*cylinder(char **tmp)
{
	t_cy		*cy;
	char		**xyz;

	if (len_2d(tmp) != 6)
		error("ERROR: cylinder");
	cy = malloc (sizeof(t_cy));
	check_rgbstring(tmp[1]);
	check_rgbstring(tmp[2]);
	check_rgbstring(tmp[5]);
	xyz = ft_split(tmp[1], ',');
	cy->pos.x = ft_atof(xyz[0]);
	cy->pos.y = ft_atof(xyz[1]);
	cy->pos.z = ft_atof(xyz[2]);
	cy->pos.w = 1;
	free_two_arr(xyz);
	xyz = ft_split(tmp[2], ',');
	cy->normal.x = ft_atof(xyz[0]);
	cy->normal.y = ft_atof(xyz[1]);
	cy->normal.z = ft_atof(xyz[2]);
	cy->normal.w = 0;
	free_two_arr(xyz);
	xyz = ft_split(tmp[5], ',');
	cy->rgb.red = ft_atof(xyz[0]);
	cy->rgb.green = ft_atof(xyz[1]);
	cy->rgb.blue = ft_atof(xyz[2]);
	free_two_arr(xyz);
	cy->diameter = ft_atof(tmp[3]);
	cy->height = ft_atof(tmp[4]);
	check_rgb_value(cy->rgb);
	check_normalize_value(cy->normal);
	return (cy);
}

t_plane	*plane(char **tmp)
{
	t_plane		*plane;
	char		**xyz;

	if (len_2d(tmp) != 4)
		error("ERROR: plane");
	plane = malloc (sizeof(t_plane));
	check_rgbstring(tmp[1]);
	check_rgbstring(tmp[2]);
	check_rgbstring(tmp[3]);
	xyz = ft_split(tmp[1], ',');
	plane->pos.x = ft_atof(xyz[0]);
	plane->pos.y = ft_atof(xyz[1]);
	plane->pos.z = ft_atof(xyz[2]);
	plane->pos.w = 1;
	free_two_arr(xyz);
	xyz = ft_split(tmp[2], ',');
	plane->normal.x = ft_atof(xyz[0]);
	plane->normal.y = ft_atof(xyz[1]);
	plane->normal.z = ft_atof(xyz[2]);
	plane->normal.w = 0;
	free_two_arr(xyz);
	xyz = ft_split(tmp[3], ',');
	plane->rgb.red = ft_atof(xyz[0]);
	plane->rgb.green = ft_atof(xyz[1]);
	plane->rgb.blue = ft_atof(xyz[2]);
	free_two_arr(xyz);
	check_rgb_value(plane->rgb);
	check_normalize_value(plane->normal);
	return (plane);
}

t_sphere *sphere(char **tmp)
{
	t_sphere	*sphere;
	char		**xyz;

	if (len_2d(tmp) != 4)
		error("ERROR: sphere");
	sphere = malloc (sizeof(t_sphere));
	check_rgbstring(tmp[1]);
	check_rgbstring(tmp[3]);
	xyz = ft_split(tmp[1], ',');
	sphere->pos.x = ft_atof(xyz[0]);
	sphere->pos.y = ft_atof(xyz[1]);
	sphere->pos.z = ft_atof(xyz[2]);
	sphere->pos.w = 1;
	free_two_arr(xyz);
	sphere->diameter = ft_atof(tmp[2]);
	xyz = ft_split(tmp[3], ',');
	sphere->rgb.red = ft_atof(xyz[0]);
	sphere->rgb.green = ft_atof(xyz[1]);
	sphere->rgb.blue = ft_atof(xyz[2]);
	free_two_arr(xyz);
	check_rgb_value(sphere->rgb);
	return (sphere);
}