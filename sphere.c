/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:57:49 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/18 07:48:42 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// init sphere
void sphereInit(t_sphere *sphere, t_ambient ambient)
{
    sphere->transform = matrixMult(get_matrix(sphere->pos.x, sphere->pos.y, sphere->pos.z, 't'), get_matrix(sphere->diameter, sphere->diameter, sphere->diameter, 's'));
    sphere->pos = vectorInit(0, 0, 0, 1);
    sphere->material = materials(sphere->rgb, ambient.ratio);
}

// get the intersection of a ray with a sphere
double sphereIntersection(t_sphere s, ray r)
{
    double A;
    double B;
    double C;
    double t1;
    double t2;
    t_vector v;
    double tmp;
    double discriminant;
    ray r2;

    r2 = transform(r, s.transform, -1);
    // t = malloc(sizeof(double) * 2);

    // print_vector(r2.start);

    v = vectorSub(r2.start, s.pos);
    A = vectorDot(r2.dir, r2.dir);
    B = 2 * vectorDot(r2.dir, v);
    C = vectorDot(v, v) - 1;
    discriminant =  B * B - 4 * A * C; 
    
    if (discriminant < 0)
        return (-1);
    else
    {
        t1 = (-B - sqrt(discriminant)) / (2 * A);
        t2 = (-B + sqrt(discriminant)) / (2 * A);

        if(t1 > t2)
                t1 = t2;

        if((t1 > 0.001f))
            return t1;
        else
            return (-1);
    }
}

// get the normal vector in a sphere
t_vector normal_at_sphere(t_sphere s, t_vector p)
{
    t_vector obj_p = vector_mult_matrix(p, s.transform, -1);
    t_vector obj_n = vectorSub(obj_p, s.pos);
    t_vector world_n = vector_mult_matrix(obj_n, matrixTranspose(matrixInverse(s.transform)), 1);

    world_n.w = 0;

    return normalize(world_n);
}

// get the reflect vector of in vector
t_vector reflect(t_vector in, t_vector normal)
{
	return vectorSub(in, vectorScale(normal, 2 * vectorDot(in, normal)));
}