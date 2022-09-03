/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:57:49 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/03 19:42:37 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// init sphere
void	sphere_init(t_sphere *sphere, t_ambient ambient)
{
	sphere->transform = matrix_mult(
			get_matrix(sphere->pos.x, sphere->pos.y, sphere->pos.z, 't'),
			get_matrix(sphere->diameter,
				sphere->diameter, sphere->diameter, 's'));
	sphere->inverted_transform = matrix_inverse(sphere->transform);
	sphere->pos = vector_init(0, 0, 0, 1);
	sphere->material = materials(sphere->rgb, ambient.ratio, sphere->shiness);
}

// get the intersection of a t_ray with a sphere
double	sphere_intersection(t_sphere s, t_ray r)
{
	t_delta		delta;
	t_vector	v;
	t_ray		r2;
	double		t1;
	double		t2;

	// printf("test=> %f\n", s.inverted_transform.m[0][0]);
	r2 = transform(r, s.inverted_transform, 1);
	v = vector_sub(r2.start, s.pos);
	delta.a = vector_dot(r2.dir, r2.dir);
	delta.b = 2 * vector_dot(r2.dir, v);
	delta.c = vector_dot(v, v) - 1;
	delta.discriminant = delta.b * delta.b - 4 * delta.a * delta.c;
	if (delta.discriminant < 0)
		return (-1);
	else
	{
		t1 = (-delta.b - sqrt(delta.discriminant)) / (2 * delta.a);
		t2 = (-delta.b + sqrt(delta.discriminant)) / (2 * delta.a);
		if (t1 > t2)
			t1 = t2;
		if ((t1 > RAY_T_MIN))
			return (t1);
		else
			return (-1);
	}
}

// get the normal vector in a sphere
t_vector	normal_at_sphere(t_sphere s, t_vector p)
{
	t_vector	obj_p;
	t_vector	obj_n;
	t_vector	world_n;
	obj_p = vector_mult_matrix(p, s.inverted_transform, 1);
	obj_n = vector_sub(obj_p, s.pos);
	world_n = vector_mult_matrix(obj_n,
			matrix_transpose(s.inverted_transform), 1);
	world_n.w = 0;
	return (normalize(world_n));
}

// get the reflect vector of in vector
t_vector	reflect(t_vector in, t_vector normal)
{
	return (vector_sub(in, vector_scale(normal, 2 * vector_dot(in, normal))));
}
