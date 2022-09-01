/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 23:30:25 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/31 11:21:50 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// get the position where the intersection occured
t_vector	position(ray r, double t)
{
	return (vector_add(r.start, vector_scale(r.dir, t)));
}

// transform the ray
ray	transform(ray r, t_matrix m, int type)
{
	ray	new_ray;

	new_ray.start = vector_mult_matrix(r.start, m, type);
	new_ray.dir = vector_mult_matrix(r.dir, m, type);
	return (new_ray);
}

// get the ray tha passes through x ans y
ray	ray_for_pixel(t_camera camera, int x, int y)
{
	ray			r;
	t_vector	pixel;
	double		world_x;
	double		world_y;

	world_x = camera.half_width - (x + 0.5) * camera.pixel_size;
	world_y = camera.half_height - (y + 0.5) * camera.pixel_size;
	pixel = vector_mult_matrix(vector_init(
				world_x, world_y, -1, 1), camera.transform, -1);
	r.start = vector_mult_matrix(vector_init(0, 0, 0, 1), camera.transform, -1);
	r.dir = normalize(vector_sub(pixel, r.start));
	return (r);
}
