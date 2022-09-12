/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:55:28 by ael-bach          #+#    #+#             */
/*   Updated: 2022/09/11 14:02:29 by yed-dyb          ###   ########.fr       */
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

t_RGB	fill_rgb(char *tmp)
{
	t_RGB	rgb;
	char	**xyz;

	xyz = ft_split(tmp, ',');
	rgb.red = ft_atof(xyz[0]);
	rgb.green = ft_atof(xyz[1]);
	rgb.blue = ft_atof(xyz[2]);
	free_two_arr(xyz);
	return (rgb);
}

t_cy	*cylinder(char **tmp)
{
	t_cy		*cy;
	char		**xyz;

	if (len_2d(tmp) != 8)
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
	cy->rgb = fill_rgb(tmp[5]);
	cy->diameter = ft_atof(tmp[3]) / 10.0;
	cy->height = ft_atof(tmp[4]) / 10.0;
	cy->shiness = ft_atof(tmp[6]);
	is_between(0, 500, cy->shiness);
	cy->reflective = ft_atof(tmp[7]);
	is_between(0, 1, cy->reflective);
	check_rgb_value(cy->rgb);
	check_normalize_value(cy->normal);
	return (cy);
}

t_cube	*cube(char **tmp)
{
	t_cube		*cube;
	char		**xyz;

	if (len_2d(tmp) != 9)
		error("ERROR: cube");
	cube = malloc (sizeof(t_cube));
	check_rgbstring(tmp[1]);
	check_rgbstring(tmp[2]);
	check_rgbstring(tmp[6]);
	xyz = ft_split(tmp[1], ',');
	cube->pos = fill_vector(xyz, 1, 10);
	free_two_arr(xyz);
	xyz = ft_split(tmp[2], ',');
	cube->normal = fill_vector(xyz, 0, 1);
	free_two_arr(xyz);
	cube->width = ft_atof(tmp[3]) / 10.0;
	cube->height = ft_atof(tmp[4]) / 10.0;
	cube->length = ft_atof(tmp[5]) / 10.0;
	cube->rgb = fill_rgb(tmp[6]);
	cube->shiness = ft_atof(tmp[7]);
	is_between(0, 500, cube->shiness);
	cube->reflective = ft_atof(tmp[8]);
	is_between(0, 1, cube->reflective);
	check_rgb_value(cube->rgb);
	check_normalize_value(cube->normal);
	return (cube);
}


t_plane	*plane(char **tmp)
{
	t_plane		*plane;
	char		**xyz;

	if (len_2d(tmp) < 6 || len_2d(tmp) > 8)
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
	plane->rgb = fill_rgb(tmp[3]);
	plane->shiness = ft_atof(tmp[4]);
	is_between(0, 500, plane->shiness);
	plane->reflective = ft_atof(tmp[5]);
	is_between(0, 1, plane->reflective);
	if (tmp[6])
	{
		plane->rgbcheck = plane_optional(tmp[6]);
		if (tmp[7] && tmp[7][0])
			plane->stripe_type = tmp[7][0];
		else
			plane->stripe_type = 'c';
	}
	else
		plane->rgbcheck = fill_rgb("-1,-1,-1");
	check_rgb_value(plane->rgb);
	check_normalize_value(plane->normal);
	return (plane);
}

t_sphere	*sphere(char **tmp)
{
	t_sphere	*sphere;
	char		**xyz;

	if (len_2d(tmp) != 6)
		error("ERROR: sphere");
	sphere = malloc (sizeof(t_sphere));
	check_rgbstring(tmp[1]);
	check_rgbstring(tmp[3]);
	xyz = ft_split(tmp[1], ',');
	sphere->pos = fill_vector(xyz, 1, 10);
	free_two_arr(xyz);
	sphere->diameter = ft_atof(tmp[2]) / 10;
	sphere->rgb = fill_rgb(tmp[3]);
	sphere->shiness = ft_atof(tmp[4]);
	is_between(0, 500, sphere->shiness);
	sphere->reflective = ft_atof(tmp[5]);
	is_between(0, 1, sphere->reflective);
	check_rgb_value(sphere->rgb);
	return (sphere);
}
