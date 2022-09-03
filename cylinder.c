/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:14:35 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/03 18:10:57 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	cylinder_init(t_cy *cy, t_ambient ambient)
{
	cy->transform = matrix_mult(matrix_mult(matrix_mult(
					get_matrix(cy->pos.x, cy->pos.y, cy->pos.z, 't'),
					get_rotation_matrix(cy->normal.x, 'x')),
					get_rotation_matrix(cy->normal.y, 'y')),
				get_rotation_matrix(cy->normal.z, 'z'));
	cy->inverted_transform = matrix_inverse(cy->transform);
	cy->pos = vector_init(0, 0, 0, 1);
	cy->material = materials(cy->rgb, ambient.ratio);
	cy->min = 0;
	cy->max = cy->height;
}

double	is_hit(t_cy cy, t_ray r, double t0, double t1)
{
	double	y0;
	double	y1;

	y0 = r.start.y + t0 * r.dir.y;
	y1 = r.start.y + t1 * r.dir.y;
	if (t0 > RAY_T_MIN && cy.min < y0 && y0 < cy.max)
		return (t0);
	else if (t1 > RAY_T_MIN && cy.min < y1 && y1 < cy.max)
		return (t1);
	else
		return (-1);
}

double	cylinder_intersection(t_cy cy, t_ray r)
{
	double	t0;
	double	t1;
	t_delta	delta;
	t_ray	r2;

	r2 = transform(r, cy.inverted_transform, 1);
	delta.a = r2.dir.x * r2.dir.x + r2.dir.z * r2.dir.z;
	if (delta.a < 0)
		return (-1);
	delta.b = 2 * r2.start.x * r2.dir.x + 2 * r2.start.z * r2.dir.z;
	delta.c = r2.start.x * r2.start.x + r2.start.z
		* r2.start.z - cy.diameter * cy.diameter;
	delta.discriminant = delta.b * delta.b - 4 * delta.a * delta.c;
	if (delta.discriminant < 0)
		return (-1);
	else
	{
		t0 = (-delta.b - sqrt(delta.discriminant)) / (2 * delta.a);
		t1 = (-delta.b + sqrt(delta.discriminant)) / (2 * delta.a);
		return (is_hit(cy, r2, t0, t1));
	}
}

t_vector	normal_at_cylinder(t_cy cy, t_vector p)
{
	t_vector	obj_p;
	t_vector	obj_n;
	t_vector	world_n;

	obj_p = vector_mult_matrix(p, cy.inverted_transform, 1);
	obj_n = vector_init(obj_p.x, 0, obj_p.z, 0);
	world_n = vector_mult_matrix(obj_n,
			matrix_transpose(cy.inverted_transform), 1);
	world_n.w = 0;
	return (normalize(world_n));
}
