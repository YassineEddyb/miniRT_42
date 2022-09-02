/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:55:28 by ael-bach          #+#    #+#             */
/*   Updated: 2022/09/02 15:36:42 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

t_vector	fill_vector(char **xyz, int _w, int dv)
{
	t_vector	vc;

	vc.x = ft_atof(xyz[0]) / dv;
	vc.y = ft_atof(xyz[1]) / dv;
	vc.z = ft_atof(xyz[2]) / dv;
	vc.w = _w;
	return (vc);
}

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
	cy->pos = fill_vector(xyz, 1, 10);
	free_two_arr(xyz);
	xyz = ft_split(tmp[2], ',');
	cy->normal = fill_vector(xyz, 0, 1);
	free_two_arr(xyz);
	xyz = ft_split(tmp[5], ',');
	cy->rgb.red = ft_atof(xyz[0]);
	cy->rgb.green = ft_atof(xyz[1]);
	cy->rgb.blue = ft_atof(xyz[2]);
	free_two_arr(xyz);
	cy->diameter = ft_atof(tmp[3]) / 10.0;
	cy->height = ft_atof(tmp[4]) / 10.0;
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
	plane->pos = fill_vector(xyz, 1, 10);
	free_two_arr(xyz);
	xyz = ft_split(tmp[2], ',');
	plane->normal = fill_vector(xyz, 0, 1);
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

t_sphere	*sphere(char **tmp)
{
	t_sphere	*sphere;
	char		**xyz;

	if (len_2d(tmp) != 4)
		error("ERROR: sphere");
	sphere = malloc (sizeof(t_sphere));
	check_rgbstring(tmp[1]);
	check_rgbstring(tmp[3]);
	xyz = ft_split(tmp[1], ',');
	sphere->pos = fill_vector(xyz, 1, 10);
	free_two_arr(xyz);
	sphere->diameter = ft_atof(tmp[2]) / 10;
	xyz = ft_split(tmp[3], ',');
	sphere->rgb.red = ft_atof(xyz[0]);
	sphere->rgb.green = ft_atof(xyz[1]);
	sphere->rgb.blue = ft_atof(xyz[2]);
	free_two_arr(xyz);
	check_rgb_value(sphere->rgb);
	return (sphere);
}
