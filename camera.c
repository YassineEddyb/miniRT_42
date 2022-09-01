/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:46:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/28 14:33:59 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// init camera
void	camera_init(t_camera *camera, double hsize, double vsize)
{
	t_vector	up;
	double		half_view;
	double		aspect;

	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->transform = get_matrix(0, 0, 0, 'i');
	camera->fov = camera->fov * M_PI / 180;
	half_view = tan(camera->fov / 2);
	aspect = hsize / vsize;
	if (aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;
	up = vectorInit(0, 1, 0, 0);
	camera->transform = view_transform(camera->pos, camera->normal, up);
}

// transform the view of the camera
t_matrix	view_transform(t_vector from, t_vector to, t_vector up)
{
	t_vector	forward;
	t_vector	left;
	t_vector	true_up;
	t_matrix	or;
	t_matrix	m;

	forward = normalize(vectorSub(to, from));
	left = vectorCross(forward, normalize(up));
	true_up = vectorCross(left, forward);
	or = matrix_create(4, 4);
	or.m[0][0] = left.x;
	or.m[0][1] = left.y;
	or.m[0][2] = left.z;
	or.m[1][0] = true_up.x;
	or.m[1][1] = true_up.y;
	or.m[1][2] = true_up.z;
	or.m[2][0] = -forward.x;
	or.m[2][1] = -forward.y;
	or.m[2][2] = -forward.z;
	or.m[3][3] = 1;
	m = get_matrix(-from.x, -from.y, -from.z, 't');
	return (matrix_mult(or, m));
}
