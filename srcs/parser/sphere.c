/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:55:28 by ael-bach          #+#    #+#             */
/*   Updated: 2022/09/04 13:11:04 by yed-dyb          ###   ########.fr       */
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

	if (len_2d(tmp) != 7)
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
	is_between(0, 200, cy->shiness);
	check_rgb_value(cy->rgb);
	check_normalize_value(cy->normal);
	return (cy);
}

t_plane	*plane(char **tmp)
{
	t_plane		*plane;
	char		**xyz;

	if (len_2d(tmp) < 5 || len_2d(tmp) > 6)
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
	if (tmp[5])
	{
		check_rgbstring(tmp[5]);
		plane->rgbcheck = fill_rgb(tmp[5]);
		check_rgb_value(plane->rgbcheck);
	}
	else
		plane->rgbcheck = fill_rgb("-1,-1,-1");
	is_between(0, 200, plane->shiness);
	check_rgb_value(plane->rgb);
	check_normalize_value(plane->normal);
	return (plane);
}

t_sphere	*sphere(char **tmp)
{
	t_sphere	*sphere;
	char		**xyz;

	if (len_2d(tmp) != 5)
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
	is_between(0, 200, sphere->shiness);
	check_rgb_value(sphere->rgb);
	return (sphere);
}
