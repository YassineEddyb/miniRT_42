/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:57:49 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/16 16:55:32 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// sphere sphereInit(vector transform)
// {
//     sphere s;
//     s.pos = vectorInit(0, 0, 0, 1);
//     return s;
// }

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

// init sphere
sphere shpereInit()
{
    sphere s;

    s.pos = vectorInit(0, 0, 0, 1);
    s.transform = get_matrix(0, 0, 0, 'i');
    s.material = materials();

    return s;
}

// get the normal vector in a sphere
vector normal_at_sphere(sphere s, vector p)
{
    vector obj_p = vector_mult_matrix(p, s.transform, -1);
    vector obj_n = vectorSub(obj_p, s.pos);
    vector world_n = vector_mult_matrix(obj_n, matrixTranspose(matrixInverse(s.transform)), 1);

    world_n.w = 0;

    return normalize(world_n);
}

// get the reflect vector of in vector
vector reflect(vector in, vector normal)
{
	return vectorSub(in, vectorScale(normal, 2 * vectorDot(in, normal)));
}