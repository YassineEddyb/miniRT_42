/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:14:47 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/03 21:25:55 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	plane_init(t_plane *plane, t_ambient ambient)
{
	plane->transform = matrix_mult(matrix_mult(matrix_mult(
					get_matrix(plane->pos.x, plane->pos.y, plane->pos.z, 't'),
					get_rotation_matrix(rad(plane->normal.x), 'x')),
				get_rotation_matrix(rad(plane->normal.y), 'y')),
			get_rotation_matrix(rad(plane->normal.z), 'z'));
	plane->inverted_transform = matrix_inverse(plane->transform);
	plane->pos = vector_init(0, 0, 0, 1);
	plane->material = materials(plane->rgb, ambient.ratio, plane->shiness);
}

double	plane_intersection(t_plane plane, t_ray r)
{
	t_ray	r2;
	double	t;

	r2 = transform(r, plane.inverted_transform, 1);
	if (fabs(r2.dir.y) < RAY_T_MIN)
		return (-1);
	t = -r2.start.y / r2.dir.y;
	if (t > RAY_T_MIN)
		return (t);
	else
		return (-1);
}

t_vector	normal_at_plane(t_plane plane)
{
	t_vector	normal;
	t_vector	obj_p;
	t_vector	world_n;

	normal = vector_init(0, 1, 0, 0);
	obj_p = vector_mult_matrix(normal, plane.inverted_transform, 1);
	world_n = vector_mult_matrix(obj_p,
			matrix_transpose(plane.inverted_transform), 1);
	world_n.w = 0;
	return (normalize(world_n));
}
