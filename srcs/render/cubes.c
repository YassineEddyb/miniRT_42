/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:55:10 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/11 12:56:03 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/miniRT.h"

void print_matrix(t_matrix m)
{
   int j;
   int i = 0;
   while(i < m.rows)
   {
      j = 0;
      while(j < m.cols)
      {
         printf("%f|", m.m[i][j]);
         j++;
      }
      printf("\n");
      i++;
   }
   printf("\n");
}

void cube_init(t_cube *cube, t_ambient ambient)
{
	cube->transform = matrix_mult(matrix_mult(matrix_mult(matrix_mult(
					get_matrix(cube->pos.x, cube->pos.y, cube->pos.z, 't'),
					get_rotation_matrix(rad(cube->normal.x), 'x')),
				get_rotation_matrix(rad(cube->normal.y), 'y')),
			get_rotation_matrix(rad(cube->normal.z), 'z')),
        get_matrix(cube->width, cube->height, cube->length, 's'));
	cube->inverted_transform = matrix_inverse(cube->transform);
	cube->transposed_matrix = matrix_transpose(cube->inverted_transform);
	cube->pos = vector_init(0, 0, 0, 1);
	cube->material = materials(cube->rgb, ambient.ratio, cube->shiness, cube->reflective);
	// cube->min = 0;
	// cube->max = cube->height;
}

double  *check_axis(double origin, double dir)
{
    double t_min = (-1 - origin);
    double t_max = (1 - origin);
    double *t;
    double tmp;

    t = calloc(3, sizeof(double));

    if (fabs(dir) > FLT_EPSILON)
    {
        t[0] = t_min / dir;
        t[1] = t_max / dir;

        if (t[0] > t[1])
        {
            tmp = t[0];
            t[0] = t[1];
            t[1] = tmp;
        }
    }
    return (t);
}

double	cube_intersection(t_cube cube, t_ray r)
{
    t_ray r2;
    double *xt;
    double *yt;
    double *zt;
    double min;
    double max;

    r2 = transform(r, cube.inverted_transform, 1);

    xt = check_axis(r2.start.x, r2.dir.x);
    yt = check_axis(r2.start.y, r2.dir.y);
    zt = check_axis(r2.start.z, r2.dir.z);

    min = fmax(xt[0], fmax(yt[0], zt[0]));
    max = fmin(xt[1], fmin(yt[1], zt[1]));

    if (min > max)
        return (-1);
    if (min > RAY_T_MIN)
        return (min);
    else 
        return (-1);
}

t_vector	normal_at_cube(t_cube cube, t_vector point)
{
	t_vector	normal;
	t_vector	obj_p;
	t_vector	world_n;
    double maxc;

	obj_p = vector_mult_matrix(point, cube.inverted_transform, 1);

    maxc = fmax(fabs(obj_p.x), fmax(fabs(obj_p.y), fabs(obj_p.z)));
    if (maxc == fabs(obj_p.x))
	    normal = vector_init(obj_p.x, 0, 0, 1);
    else if (maxc == fabs(obj_p.y))
	    normal = vector_init(0, obj_p.y, 0, 1);
    else
	    normal = vector_init(0, 0, obj_p.z, 1);

	world_n = vector_mult_matrix(normal, cube.transposed_matrix, 1);
	world_n.w = 0;
	return (normalize(world_n));
}
