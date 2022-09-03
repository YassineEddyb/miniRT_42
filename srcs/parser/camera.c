/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:54:18 by ael-bach          #+#    #+#             */
/*   Updated: 2022/09/03 18:23:56 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

void	is_between(float small, float big, float nbr)
{
	if (nbr > big || nbr < small)
		error("ERROR : VALUE OUT OF RANGE");
}

void	*check_normalize_value(t_vector pos)
{
	if (pos.x > 1 || pos.x < -1)
		error("ERROR : X NORMALIZE VALUE OUT OF RANGE");
	if (pos.y > 1 || pos.y < -1)
		error("ERROR : Y NORMALIZE VALUE OUT OF RANGE");
	if (pos.z > 1 || pos.z < -1)
		error("ERROR : Z NORMALIZE VALUE OUT OF RANGE");
	return ("OK");
}

void	*check_rgb_value(t_RGB rgb)
{
	if (rgb.red > 255 || rgb.red < 0)
		error("ERROR : RGB VALUE OUT OF RANGE");
	if (rgb.green > 255 || rgb.green < 0)
		error("ERROR : RGB VALUE OUT OF RANGE");
	if (rgb.blue > 255 || rgb.blue < 0)
		error("ERROR : RGB VALUE OUT OF RANGE");
	return ("OK");
}

t_camera	*camera(char **info)
{
	t_camera	*camera;
	char		**xyz;

	if (len_2d(info) != 4)
		error("ERROR: CAMERA");
	camera = malloc (sizeof(t_camera));
	check_rgbstring(info[1]);
	check_rgbstring(info[2]);
	xyz = ft_split(info[1], ',');
	camera->pos = fill_vector(xyz, 1, 10);
	free_two_arr(xyz);
	xyz = ft_split(info[2], ',');
	camera->normal = fill_vector(xyz, 0, 1);
	free_two_arr(xyz);
	camera->fov = ft_atof(info[3]);
	check_normalize_value(camera->normal);
	is_between(0, 180, camera->fov);
	return (camera);
}
