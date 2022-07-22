/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:54:18 by ael-bach          #+#    #+#             */
/*   Updated: 2022/07/22 15:16:56 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

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
	camera->pos.x = ft_atof(xyz[0]);
	camera->pos.y = ft_atof(xyz[1]);
	camera->pos.z = ft_atof(xyz[2]);
	free_two_arr(xyz);
	xyz = ft_split(info[2], ',');
	camera->normal.x = ft_atof(xyz[0]);
	camera->normal.y = ft_atof(xyz[1]);
	camera->normal.z = ft_atof(xyz[2]);
	free_two_arr(xyz);
	camera->fov = ft_atoi(info[3]);
	return (camera);
}